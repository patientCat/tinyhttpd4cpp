#pragma once
#include "MutexLockGuard.hh"
#include "Condition.hh"

class CountDownLatch
{
public:
    CountDownLatch(int );

    void wait();
    void countDown();
    int getCount() const;

private:
    mutable MutexLock mutex_;
    Condition cond_;
    int cnt_;
};
