//c++ program
//design by >^.^<
//@date    2019-06-03 00:51:05
#include "TcpConnection.hh"
#include "Reactor.hh"
#include "Socket.hh"
#include "../base/Logging.hh"

namespace singsing{

TcpConnection::TcpConnection(Reactor* reactor, int connfd)
: reactor_(reactor)
, connFd_(connfd)
, handler_(connfd)
, inputBuffer_()
, outputBuffer_()
, state_(kConnected)
{

}

TcpConnection::~TcpConnection()
{
    ::close(connFd_);
}

void
TcpConnection::registerHandler()
{
    handler_.setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    handler_.setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    handler_.enableRead();
    reactor_->registerHandler(&handler_);
    connectionCallback_(shared_from_this());
}

void 
TcpConnection::handleRead(Timestamp when)
{
    int savedErrno = 0;
    int n = inputBuffer_.readFd(connFd_, &savedErrno);
    if(n > 0)
    {
        if(messageCallback_)
            messageCallback_(shared_from_this(), &inputBuffer_, when);
    }
    else // 直接错误处理和断开连接一起处理了
    {
        // 这里还有一些收尾工作
        reactor_->removeHandler(&handler_);
        closeCallback_(shared_from_this());
    }
}

// 为什么写缓冲区的设置
// send的目的是将数据发送内核写缓冲区，当写缓冲区满了的时候，会将
// 非线程安全的
void 
TcpConnection::send(const void*data, size_t len)
{
    ssize_t nwrite = 0;
    // 如果写缓冲区为空且不在向内核写，则直接写
    if(!handler_.isWriting() && outputBuffer_.readableSize() == 0) 
    {
        nwrite = ::write(connFd_, data, len);
        if(nwrite > 0)
        {
            if((size_t)nwrite == len && writeCompleteCallback_)
                writeCompleteCallback_(shared_from_this());
        }
        else if(nwrite == 0)
        {
            closeCallback_(shared_from_this());
        }
        else{
           //
        }
    }
    // 如果缓冲区有数据，或者正在写，或者数据一次性没写完
    if(nwrite < len || handler_.isWriting() || outputBuffer_.readableSize() > 0)
    {
        outputBuffer_.append(static_cast<const char*>(data) + nwrite, len - nwrite);
        if(!handler_.isWriting())
        {
            handler_.enableWrite();
            reactor_->registerHandler(&handler_);
        }
    }
}
void 
TcpConnection::send(std::string str)
{
    send(str.data(), str.size());
}

/*
 * 存在安全隐患，这里可以成功的前提是建立在对端发现本端关闭连接后，对端也会关闭
 * 如果对端恶意不关闭，就会保持连接一直存在
 *
 * 半关闭的目的是为了让当fd关闭时，此时如果对端有数据在路上，这样可以接受到
 */
void 
TcpConnection::shutdown()
{
    reactor_->addTask(std::bind(&TcpConnection::shutdownInReactor, this));
}

void 
TcpConnection::shutdownInReactor()
{
    state_ = kDisconnected;
    if(!handler_.isWriting())
    {
        // 半关闭
        SocketUtil::shutdownWrite(connFd_);
    }
}

void
TcpConnection::handleWrite()
{
    // 如果handler注册了写事件，handleWirte才会被真正调用，否则会错误
    if(handler_.isWriting())
    {
        int n = write(handler_.fd(), outputBuffer_.readIndexPtr(), outputBuffer_.readableSize());
        if(n > 0)
        {
            outputBuffer_.updateReadIndex(n);
            if(outputBuffer_.readableSize() == 0) // 应用层写缓冲区数据发送完毕
            {
                handler_.disableWrite();
                reactor_->registerHandler(&handler_);
                if(writeCompleteCallback_)
                    writeCompleteCallback_(shared_from_this());
                if(state_ == kDisconnected)
                    shutdownInReactor();
            }
        }
        else{
            // 如果没有向写缓冲区写任何数据，此时该handler的写状态依然就序。epoll不会wait，直接返回。
            // 这里实际上可以考虑高水位情况。即这里需要放慢写的速度。在muduo中有对应实现。这里就不再做了。
        }
    }
    else{
        LOG_ERROR << "this conn_handler does not enableWrite"; 
    }
}

}// end singsing
