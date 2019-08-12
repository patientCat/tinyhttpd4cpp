//c++ program
//design by >^.^<
//@date    2019-06-13 05:05:56
#include "Reactor.hh"
#include "EpollPoller.hh"
#include "Handler.hh"
#include "../base/CurrentThread.hh"
#include "../base/Logging.hh"

#include <sys/eventfd.h>
#include <sys/timerfd.h>

/*
 * 这里的主要任务逻辑如下
 * while(1)
 * {
 *   auto activeEventsList = poller.poll();
 *   for(auto event: activeEventList)
 *      event.handeEvent();
 *   handleTask(); // 当没有任务的时候, 这里可能会发生阻塞，一旦有任务添加，这里就会继续下去
 * }
 */

namespace singsing{

Reactor::Reactor()
: quit_(false)
, wakeupFd_(eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC))
, wakeupHandler(new Handler(wakeupFd_))
, poller_(new EpollPoller())
, isHandleTask(false)
, timerQueue_(new TimerQueue(this))
, threadId_(CurrentThread::tid())
{
    if(wakeupFd_ < 0)
    {
        LOG_ERROR << "create wakeupFd_ failed";
    }
    wakeupHandler->setReadCallback(std::bind(&Reactor::handleWakeup, this));
    wakeupHandler->enableRead();
    registerHandler(wakeupHandler.get());
}

Reactor::~Reactor()
{
    ::close(wakeupFd_);
}

void 
Reactor::registerHandler(Handler* handler)
{
    poller_->update(handler);
}

void
Reactor::removeHandler(Handler* handler) {
    poller_->remove(handler);
}

void 
Reactor::loop()
{
    while(1)
    {
        auto activeEventPtrList = poller_->poll();
        if(!activeEventPtrList.empty())
        {
            for(int i = 0; i < activeEventPtrList.size(); ++i)
            {
                activeEventPtrList[i]->handleEvent();
            }
        }
        else{
        }

        handleTask();
    }
}

// 唤醒循环，怎么唤醒呢，就是利用一个fd，写一个字节进去通知就可以
void 
Reactor::wakeUp()
{
    // 注意这里eventfd中必须使用8个字节的变量
    uint64_t one = 1;
    int n = ::write(wakeupFd_, &one, sizeof(one));
    if(n != sizeof(one))
    {
        LOG_ERROR << "wake up error in write()";
    }
}

// 用来处理唤醒事件
void 
Reactor::handleWakeup()
{
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof one);
    if( n != sizeof one)
    {
        LOG_ERROR << "handle wake up error in read()";
    }
}

// 线程安全的调用
void 
Reactor::runTask(Task&& task)
{
    if(isInReactorThread())
        task();
    // 如果不是在自己所在的线程调用，则添加进任务队列
    else
        addTask(std::move(task));
}

// 向BlokingQueue中添加任务
void
Reactor::addTask(Task&& task)
{
    taskQueue_.put(std::move(task));

    // 如果不是在Reactor所在的线程的话，或者
    if(!isInReactorThread() || isHandleTask)
    {
        wakeUp();
    }    
}

void 
Reactor::handleTask()
{
    // 这里不需要加锁，即使在handleTask任务的时候，他们添加任务，这里面只会固定执行size个任务，后续添加的会在下一轮执行
    // 因为只有Reactor自己可以去调用get
    isHandleTask = true;
    Task task = 0;
    int size = taskQueue_.size();
    for(int i = 0; i < size; ++i)
    {
        // 当没有任务的时候，这里会发生阻塞，但是这里使用size来这样做
        // 就不会触发阻塞
        task = taskQueue_.get();
        CurrentThread::tid();
        std::string id(CurrentThread::tidString());
        if(task)
        {
          LOG_INFO << id << " is running task()";
          task(); 
        }
    }
    isHandleTask = false;
}

void 
Reactor::runTaskAfter(Task && task, double timeout)
{
    Timestamp when = addTime(Timestamp::now(), timeout);
    timerQueue_->addTimer(task, when);
}

} // end singsing
