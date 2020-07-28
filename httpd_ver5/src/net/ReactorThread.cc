//c++ program
//design by >^.^<
//@date    2019-06-15 06:18:26
#include "ReactorThread.hh"
#include "Reactor.hh"
#include "../base/CurrentThread.hh"
#include "../base/Logging.hh"
#include "../base/MutexLockGuard.hh"
#include <pthread.h>

namespace singsing{


// ReactorThread
ReactorThread::ReactorThread()
: reactor_(NULL)
, mutex_()
, cond_(mutex_)
{
}

ReactorThread::~ReactorThread() {
    pthread_join(threadId_, NULL);
}


void 
ReactorThread::start()
{
    int ret = pthread_create(&threadId_, NULL, threadFunc, this);
    if(ret != 0)
    {
        LOG_ERROR << "pthread_create";
    }
}

void 
ReactorThread::run()
{
    tid_ = CurrentThread::tid();
    LOG_INFO << " [thread: " << tid_ << " has initialized]";
    Reactor reactor;
    {
        MutexLockGuard guard(mutex_);
        reactor_ = &reactor; 
        cond_.notify_one();
    }
    reactor.loop();
}

void *
ReactorThread::threadFunc(void *arg)
{
    ReactorThread *p = static_cast<ReactorThread*>(arg);
    p->run();
    return nullptr;
}
// 配合条件变量，使得reactor_指针得到值才返回
Reactor* 
ReactorThread::getLoop()
{
    {
        MutexLockGuard guard(mutex_);
        while(reactor_ == NULL)
        {
            cond_.wait();
        }
    }
    return reactor_;
}

}
