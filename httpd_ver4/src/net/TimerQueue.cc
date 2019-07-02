//c++ program
//design by >^.^<
//@date    2019-06-16 01:11:25
#include "TimerQueue.hh"

#include "Reactor.hh"
#include "Handler.hh"
#include "../base/Logging.hh"
#include <sys/timerfd.h>

namespace singsing{


namespace{
    int createTimerFd()
    {
        int fd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
        if(fd < 0)
        {
            LOG_SYSERR << "timerfd_create failed";
        }
        return fd;
    }

    void setTimeInTimerFd(int fd, itimerspec newvalue)
    {
        timerfd_settime(fd, 0, &newvalue, NULL);
    }

    timespec timeFromToNow(Timestamp high, Timestamp now)
    {
        timespec ret;
        int64_t microSecondsGap = high.microSecondsSinceEpoch() - now.microSecondsSinceEpoch();
        if(microSecondsGap < 100)
        {
            microSecondsGap = 100;
        }
        ret.tv_sec = microSecondsGap / Timestamp::kMicroSecondsPerSecond;
        ret.tv_nsec = (microSecondsGap % Timestamp::kMicroSecondsPerSecond) * 1000000;
        return ret;
    }
}// 匿名空间

// 创建timerfd，并将其做成事件，然后让事件关注读，然后向reactor进行注册
TimerQueue::TimerQueue(Reactor* reactor)
: reactor_(reactor)
, timerFd_(createTimerFd())
, timerFdHandler_(new Handler(timerFd_))
{
    timerFdHandler_->enableRead();
    timerFdHandler_->setReadCallback(std::bind(&TimerQueue::handleTimerExpired, this, std::placeholders::_1));
    reactor_->registerHandler(timerFdHandler_.get());
}

TimerQueue::~TimerQueue()
{
    ::close(timerFd_);
}

// 向小根堆里面添加定时器

void
TimerQueue::addTimer(TimerCallback cb, Timestamp when) // 这里的when一定是未来时间，注意这里全部都使用的是绝对时间
{
    reactor_->addTask(std::bind(&TimerQueue::addTimerInReactor, this, cb, when));
}
void
TimerQueue::addTimerInReactor(TimerCallback cb, Timestamp when)
{
    TimerPtr timerPtr(new Timer(cb, when));
    // 如果队列为空，或者新插入的定时器exptime小于队首的实现，就要重新调整timerfd的时间
    if(timerQueue_.empty() || timerPtr->getExpTime() < timerQueue_.top()->getExpTime())
       resetTimerfd(timerFd_, when); 
    timerQueue_.push(timerPtr);
}

// 目的是更新timerfd的时间
void
TimerQueue::resetTimerfd(int tfd, Timestamp when)
{
    // 返回来的是毫秒值
    itimerspec newvalue;
    memset(&newvalue, 0, sizeof newvalue);
    newvalue.it_value = timeFromToNow(when, Timestamp::now()); // 通过绝对时间来计算出相对时间差值
    setTimeInTimerFd(tfd, newvalue);
}

void 
TimerQueue::handleTimerExpired(Timestamp timestamp)
{
    uint64_t expCnt;
    int n = read(timerFd_, &expCnt, sizeof expCnt);
    if(n != sizeof(expCnt))
    {
        // handleError
    }

    auto now = Timestamp::now();
    while(!timerQueue_.empty() && timerQueue_.top()->getExpTime() < now)
    {
        timerQueue_.top()->run();
        timerQueue_.pop();
    }
    if(!timerQueue_.empty())
    {
        resetTimerfd(timerFd_, timerQueue_.top()->getExpTime());
    }
}

} // end singsing
