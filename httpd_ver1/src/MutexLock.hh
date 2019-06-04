#pragma once

#include <pthread.h>

#include <boost/noncopyable.hpp>

class MutexLock : boost::noncopyable
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex_, NULL);
    }

    void lock() // 仅供MutexLockGuard使用
    {
        pthread_mutex_lock(&mutex_);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t * getMutex()  // 仅供条件变量使用
    {
        return &mutex_;
    }

    ~MutexLock()
    {
        pthread_mutex_destroy(&mutex_);
    }
private:
    pthread_mutex_t mutex_;
};
