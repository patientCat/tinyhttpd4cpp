//c++ program
//design by >^.^<
//@date    2019-06-15 05:04:48
#include "ReactorThreadPool.hh"
#include <assert.h>

namespace  singsing{

ReactorThreadPool::ReactorThreadPool(int nums)
: threadNums_(nums)
, next_()
, isStarting_(false)
{
}

void
ReactorThreadPool::start()
{
    isStarting_ = true;
    for(int i = 0; i < threadNums_; ++i)
    {
        ReactorThread *t = new ReactorThread;
        t->start();
        reactorPtrList_.push_back(t->getLoop());
    }
}

Reactor* 
ReactorThreadPool::getNextLoop()
{
    assert(isStarting_);
    Reactor* reactor = nullptr;
    if(!reactorPtrList_.empty())
    {
        reactor = reactorPtrList_[next_];
        next_ = (next_ + 1) % threadNums_;
    }
    return reactor;
}

}// end singsing
