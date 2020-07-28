//c++ program
//design by >^.^<
//@date    2019-06-04 02:19:10
#include "ThreadPool.hh"
#include "../base/Logging.hh"

#include <pthread.h>
#include <cassert>
singsing::ThreadPool::ThreadPool(int nums, int maxsize)
: nums_(nums)
, thread_ids_(new pthread_t[nums])
, stop_(false)
, taskqueue_maxsize_(maxsize)
, countdown_(nums)
, taskqueue_()
{
    for(int i = 0; i < nums; ++i)
    {
        LOG_TRACE << "create the " << i << "th thread";
        int ret = pthread_create(&thread_ids_[i], NULL, threadFunc, static_cast<void*>(this));
        if(ret != 0)
            delete []thread_ids_;
    }
    countdown_.wait();
}

// 析构时，要保证所有线程已经被终止，否则会导致正在析构时，仍然有其他线程正在执行该对象的成员函数，无法保证这个成员函数的存在与否
// 所以主动提供stop方法，用来终止线程
singsing::ThreadPool::~ThreadPool()
{
    assert(stop_ == true);
    delete []thread_ids_;
}


void 
singsing::ThreadPool::stop()
{
    stop_ = true;
    taskqueue_.wakeup(); // 此时其他线程有俩种状态，要么空闲，要么忙碌，这里会让所有空线程线程唤醒, 忙碌线程需要继续唤醒
    for(int i = 0; i < nums_; ++i)
    {
        pthread_join(thread_ids_[i], NULL);
        taskqueue_.wakeup();
    }
}

void *
singsing::ThreadPool::threadFunc(void *arg)
{
    ThreadPool *pool = static_cast<ThreadPool*>(arg);
    pool->run();
    return pool;
}


void 
singsing::ThreadPool::run()
{
    Task task = NULL;
    countdown_.countDown();
    while(1) 
    {
        task = taskqueue_.get();
        if(!task) // task返回失败时，此时
            break;
        task();
    }
}

bool 
singsing::ThreadPool::addTask(const Task& task)
{
    if(stop_) // 线程停止时不再添加任务
        return false;
    taskqueue_.put(task);
    return true;
}

