//c++ program
//design by >^.^<
//@date    2019-06-15 00:49:01
#include "TcpServer.hh"
#include "TcpConnection.hh"
#include "../base/Logging.hh"

#include <functional>
namespace singsing{

// server初始化
TcpServer::TcpServer(Reactor & reactor, const InetAddress &addr, int num, Option o)
: serverAddress_(addr)
, base_(reactor)
, acceptor_(addr, &base_, true)
, threadNum_(num)
, threadPool_(num)
{
//    Logger::setLogLevel(Logger::LogLevel::DEBUG);
    acceptor_.setConnectionCallback(std::bind(&TcpServer::newConnection, this, std::placeholders::_1));
}

TcpServer::~TcpServer()
{
    // nothing to do
}

void
TcpServer::newConnection(int connfd)
{
    auto subReactor = threadNum_ ? threadPool_.getNextLoop() : &base_;
    // 需要创建新的连接，设置好对应的回调函数，然后将其注册到subReactor上面去
    TcpConnectionPtr connPtr(new TcpConnection(subReactor, connfd));
    static int connNum = 0;
    LOG_INFO << "connNum " << ++connNum;


    // 错误1：不能在这里回调连接到来函数，此时connPtr还没有注册到对应的subReactor上
    // connectionCallback_(connPtr); 

    connPtr->setConnectionCallback(connectionCallback_);
    connPtr->setMessageCallback(messageCallback_);
    connPtr->setWriteCompleteCallback(writeCompleteCallback_);
    // TcpConnection的销毁是一个问题
    // 首先要考虑TcpConnection链接断开的时机，是客户端去主动断开，即在我们从客户端的fd中read返回0的时候
    // 此时我们要断开连接，此时我们要将这个TcpConnection直接删除掉。然而我们自己现在还在TcpConnection的handler
    // 栈中，是无法删除的，我们需要设置一个回调函数，交给别人去做
    connPtr->setCloseCallback(std::bind(&TcpServer::removeTcpConnection, this, std::placeholders::_1));
    tcpConnectionPtrMap_[connfd] = connPtr;
    subReactor->addTask(std::bind(&TcpConnection::registerHandler, connPtr.get()));
}

void
TcpServer::removeTcpConnection(const TcpConnectionPtr& connPtr)
{
    // connectionMap本来就是属于TcpServer的，为了保证线程安全，回到TcpServer所属的线程来删除
    base_.addTask(std::bind(&TcpServer::removeTcpConnectionInBaseReactor, this, connPtr));
}

void
TcpServer::removeTcpConnectionInBaseReactor(const TcpConnectionPtr& ptr)
{
    tcpConnectionPtrMap_.erase(ptr->getFd());
}

void
TcpServer::start()
{
    threadPool_.start();
    LOG_INFO << "running on address : " << serverAddress_.getStringIpAndPort();
    base_.loop();
}

}// end singsing
