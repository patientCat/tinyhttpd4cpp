#pragma once

/*
 * 利用小根堆来实现定时器队列，后序可以采用时间轮的方式
 */

#include "../base/Timestamp.hh"
#include "Timer.hh"
#include <queue>
#include <memory>

namespace singsing
{

class Reactor;
class Handler;
class TimerQueue
{
public:
    using TimerPtr = std::shared_ptr<Timer>;
    // 绑定所属的Reactor，然后暴露一个addTimer接口，就可以将定时器加入所属的Reactor中
    TimerQueue(Reactor *);
    ~TimerQueue();


    // 一定要保证是线程安全的
    void addTimer(TimerCallback, Timestamp);
private:
    void addTimerInReactor(TimerCallback, Timestamp);
private:
    struct cmp
    {
        bool operator()(const TimerPtr&lhs, const TimerPtr&rhs)
        {
            return lhs->getExpTime() > rhs->getExpTime();
        }
    };
private:
    void resetTimerfd(int timerfd, Timestamp when);
    void handleTimerExpired(Timestamp when);


private:
    Reactor *reactor_;
    const int timerFd_; 
    std::shared_ptr<Handler> timerFdHandler_;

    // 小顶堆实现的定时器队列
    std::priority_queue<TimerPtr, std::vector<TimerPtr>, cmp> timerQueue_;
};
}// end singsing
