#pragma once

#include "MutexLock.hh"

namespace singsing{
class Condition : boost::noncopyable
{
public:
    explicit Condition(MutexLock &mutex)
    : mutex_(mutex)
    {
        pthread_cond_init(&cond_, NULL);
    }

    ~ Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void wait()
    {
        pthread_cond_wait(&cond_, mutex_.getMutex());
    }

    void notify_one()
    {
        pthread_cond_signal(&cond_);
    }

    void notify_all()
    {
        pthread_cond_broadcast(&cond_);
    }
private:
    MutexLock &mutex_;
    pthread_cond_t cond_;
};
}
