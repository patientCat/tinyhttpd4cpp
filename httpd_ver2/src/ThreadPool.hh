#pragma  once

#include "MutexLockGuard.hh"
#include "Condition.hh"
#include "CountDownLatch.hh"

#include <functional>
#include <queue>
#include <memory>

class ThreadPool : boost::noncopyable
{
    typedef std::function<void()> Task;
public:
    ThreadPool(int nums = 4, int maxsize = 10000);
    bool addTask(const Task&);
    void destroy();
    ~ThreadPool();
private:
    static void *threadFunc(void *);
    void run();
private:
    int nums_; // 用来记录线程数目
    pthread_t* thread_ids_;
    std::queue<Task> taskqueue_;
    MutexLock mutex_;
    Condition cond_;
    bool stop_;
    size_t taskqueue_maxsize_;
    CountDownLatch countdown_;
};
