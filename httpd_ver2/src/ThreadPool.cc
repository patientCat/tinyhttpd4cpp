//c++ program
//design by >^.^<
//@date    2019-06-04 02:19:10
#include "ThreadPool.hh"

#include <pthread.h>

#include <cassert>
ThreadPool::ThreadPool(int nums, int maxsize)
: nums_(nums)
, thread_ids_(new pthread_t[nums])
, mutex_() // mutex一定要先与条件变量构造
, cond_(mutex_)
, stop_(false)
, taskqueue_maxsize_(maxsize)
, countdown_(nums)
{
    for(int i = 0; i < nums; ++i)
    {
        printf("create the %dth thread\n", i);
        int ret = pthread_create(&thread_ids_[i], NULL, threadFunc, static_cast<void*>(this));
        if(ret != 0)
            delete []thread_ids_;
    }
    countdown_.wait();
}

// 析构函数要保证
ThreadPool::~ThreadPool()
{
    if(!stop_)
        destroy();
    delete []thread_ids_;
}

void 
ThreadPool::destroy()
{
    {
        MutexLockGuard guard(mutex_);
        stop_ = true;
    }
    cond_.notify_all(); // 此时其他线程有俩种状态，要么空闲，要么忙碌，这里会让所有空线程线程唤醒, 忙碌线程需要继续唤醒
    for(int i = 0; i < nums_; ++i)
    {
        pthread_join(thread_ids_[i], NULL);
        cond_.notify_all();
    }
}

void *
ThreadPool::threadFunc(void *arg)
{
    ThreadPool *pool = static_cast<ThreadPool*>(arg);
    pool->run();
    return pool;
}

void 
ThreadPool::run()
{
    Task task = NULL;
    countdown_.countDown();
    while(1) // 设置为!stop_会有一点点问题
    {
        {
            MutexLockGuard guard(mutex_);
            // 在线程池没有停止的情况下且任务队列为空的情况下，等待条件变量
            while(!stop_ && taskqueue_.empty())
            {
                cond_.wait();
            }
            if(stop_ && taskqueue_.empty()) // 如果线程池停止，就结束线程
                break;
            task = taskqueue_.front();
            taskqueue_.pop();
        }
        task();
    }
}

bool 
ThreadPool::addTask(const Task& task)
{
    {
        MutexLockGuard guard(mutex_);
        if(taskqueue_.size() > taskqueue_maxsize_ || stop_) // 线程池销毁时，不能再添加任务了
            return false;
        taskqueue_.emplace(std::move(task));
    }
    cond_.notify_one();
    return true;
}

