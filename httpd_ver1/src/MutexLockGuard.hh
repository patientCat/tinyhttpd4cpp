#pragma once

#include "MutexLock.hh"

class MutexLockGuard : boost::noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &mutex)
    : mutex_(mutex)
    {
        mutex_.lock();
    }
    ~MutexLockGuard()
    {
        mutex_.unlock();
    }
private:
    MutexLock &mutex_;
};

#define MutexLockGuard(x) static_assert(false, "missing mutex guard var name")
// 用来防止临时的MutexLockGuard，忘记写名字，导致没有锁住临界区
