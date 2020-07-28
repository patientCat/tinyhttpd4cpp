//c++ program
//design by >^.^<
//@date    2019-06-04 04:58:16
#include "CountDownLatch.hh"

namespace singsing
{
CountDownLatch::CountDownLatch(int cnt)
: mutex_()
, cond_(mutex_)
, cnt_(cnt)
{
}

void
CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_);
    while(cnt_ > 0)
    {
        cond_.wait();
    }
}

void
CountDownLatch::countDown()
{
    MutexLockGuard lock(mutex_);
    --cnt_;
    if(cnt_ == 0)
        cond_.notify_all();
}

int
CountDownLatch::getCount() const
{
    MutexLockGuard lock(mutex_);
    return cnt_;
}
}
