//c++ program
//design by >^.^<
//@date    2019-06-13 05:16:05
#include "Handler.hh"
#include <sys/epoll.h>

namespace singsing{
Handler::Handler(int fd)
: fd_(fd)
, events_(0)
, revents_(0)
, isInEpoll(false)
, len_(0)
{

}

Handler::~Handler()
{
    // close(fd)
    // Handler 并不负责关闭fd，fd的关闭应该在连接断开的时候
}


bool 
Handler::isWriting()
{
    return events_ & EPOLLOUT;
}
void 
Handler::handleEvent()
{
    // 服务器端发生异常
    if( (events_ & EPOLLHUP) && !(events_ & EPOLLIN) )
    {
        if(closeCallback_)
            closeCallback_();
        return;
    }
    // 客户端关闭连接
    if(events_ & EPOLLRDHUP)
    {
        if(closeCallback_)
            closeCallback_();
        return;
    }
    // 发生错误
    if(events_ & EPOLLERR)
    {
        return;
    }
    if(events_ & EPOLLIN)
    {
        readCallback_(Timestamp::now());
    }
    if(events_ & EPOLLOUT)
    {
        writeCallback_();
    }
}
void 
Handler::setReadCallback(ReadCallback cb)
{
    readCallback_ = cb;
}
void 
Handler::setWriteCallback(Callback cb)
{
    writeCallback_ = cb;
}
void 
Handler::setCloseCallback(Callback cb)
{
    closeCallback_ = cb;
}
void 
Handler::enableRead()
{
    events_ = EPOLLIN; 
}
void 
Handler::enableWrite()
{
    events_ = EPOLLOUT;
}
void 
Handler::enableAll()
{
    events_ |= EPOLLIN;
    events_ |= EPOLLOUT;
}
void
Handler::disableRead()
{
    events_ &= ~EPOLLIN;
}

void
Handler::disableWrite()
{
    events_ &= ~EPOLLOUT;
}
void 
Handler::disableAll()
{
    events_ = 0;
}
}// end singsing
