
/*
 * 无界的BlockingQueue
 */
#pragma once

#include "Condition.hh"
#include "MutexLockGuard.hh"

#include <deque>
#include <atomic>

namespace singsing
{
template<typename T>
class BlockingQueue
{
public:
    BlockingQueue()
    : mutex_()
    , cond_(mutex_)
    , size_(0)
    , quit_(false)
    {}

    void put(const T &x)
    {
        MutexLockGuard lock(mutex_);
        queue_.emplace_back(x);
        cond_.notify_one();
    }
    void put(const T &&x)
    {
        MutexLockGuard lock(mutex_);
        queue_.emplace_back(std::move(x));
        cond_.notify_one();
    }
    // 用来唤醒空闲队列
    void wakeup()
    {
        MutexLockGuard lock(mutex_);
        quit_ = true;
        cond_.notify_all();
    }

    T get()
    {
        MutexLockGuard lock(mutex_);
        // 只要任务队列为空就一直等待
        while(!quit_ && queue_.empty())
        {
            cond_.wait();
        }
        if(quit_ && queue_.empty())
            return NULL;

        T front(std::move(queue_.front()));
        queue_.pop_front();
        return std::move(front);
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.size();
    }
private:
    MutexLock mutex_;
    Condition cond_;
    size_t size_;
    std::deque<T> queue_;
    std::atomic_bool quit_;
};
} // namespace singsing
