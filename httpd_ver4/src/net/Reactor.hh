#pragma once

//#include "EpollPoller.hh"
#include "../base/Timestamp.hh"
#include "../base/BlockingQueue.hh"
#include "../base/CurrentThread.hh"
#include "TimerQueue.hh"
#include <memory>
#include <atomic>
#include <functional>

namespace singsing{

class Handler;
class EpollPoller;

class Reactor
{
public:
    using Task = std::function<void()>;
    Reactor();
    ~Reactor();
    void loop();
    void registerHandler(Handler* );
    void removeHandler(Handler*);
    void quit();

    void wakeUp();
    void handleWakeup();
    void runTask(Task&&);
    void addTask(Task&&);
    void handleTask();

    void runTaskAfter(Task&& task, double timeout);
    bool isInReactorThread()
    {
        return threadId_ == CurrentThread::tid();
    }
private:
    std::atomic<bool> quit_;
    int wakeupFd_;
    std::shared_ptr<Handler> wakeupHandler;
    std::unique_ptr<EpollPoller> poller_;
    BlockingQueue<Task> taskQueue_;
    std::atomic<bool> isHandleTask;
    std::unique_ptr<TimerQueue> timerQueue_;
    const pid_t threadId_;
};

}// end singsing
