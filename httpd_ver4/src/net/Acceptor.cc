//c++ program
//design by >^.^<
//@date    2019-06-15 01:23:54

#include "Acceptor.hh" 
#include "Reactor.hh"
#include "../base/Logging.hh"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <functional>
namespace singsing
{

// acceptor初始化做的事情
// 1. 将listenfd启动到listen状态
// 2. 将listenfd包装成事件，注册到reactor中去，然后暴露接口给上层
Acceptor::Acceptor(const InetAddress& addr, Reactor* base, bool reusePort)
: acceptSocket_(addr)
, base_(base)
, acceptHandler_(acceptSocket_.getFd())
, idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
    acceptSocket_.setReuseaddr(reusePort);
    acceptSocket_.setNonBlock();
    acceptSocket_.startToListen();
    acceptHandler_.setReadCallback(std::bind(&Acceptor::handleRead, this));
    acceptHandler_.enableRead();
    base->registerHandler(&acceptHandler_); // 完成listenfd的注册到EPollPoller中去
}
// 当有新连接到来的时候，接收新连接，并回调onConnection回调函数
void 
Acceptor::handleRead()
{
    int connfd = acceptSocket_.acceptOrDie();
    if(connfd > 0)
    {
        connectionCallback_(connfd);
    }
    else
    {
        LOG_SYSERR << "in Acceptor::handleRead";
        // 用来处理当文件描述值不够的情况
        // 当文件描述符不够使用的时候，先将已经占有的一个idlefd关掉，然后把连接接了，然后再关闭，然后重心让
        // idlefd回归，这样就可以保证即使文件描述符达到上限，也可以将连接接入，但是会秒断
        if(errno == EMFILE)
        {
            ::close(idleFd_);
            idleFd_ = ::accept(acceptSocket_.getFd(), NULL, NULL);
            ::close(idleFd_);
            idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
        }
    }
}

Acceptor::~Acceptor()
{
    //
    acceptHandler_.disableAll();
    // acceptHandler.remove(); == close(acceptHandler.getFd())
    // 这里涉及到延迟关闭等问题
    ::close(idleFd_);
}

}// end singsing
