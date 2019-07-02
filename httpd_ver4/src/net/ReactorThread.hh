#pragma once

#include "../base/MutexLock.hh"
#include "../base/Condition.hh"

namespace singsing
{

class Reactor;
class ReactorThread
{
    // 这个类的目的主要就是起一个线程，然后让其运行一个subReactor.loop()
    // 然后提供获得subReactor的接口，通过然后可以向这个subReactor添加任务。
    
public:
    ReactorThread();
    ~ReactorThread();

    void start();
    Reactor* getLoop();
private:
    static void* threadFunc(void*);
    void run();
    Reactor* reactor_;
    pthread_t threadId_;
    MutexLock mutex_;
    Condition cond_;
    pid_t tid_;
};
}// end singsing
