#pragma once

#include <pthread.h>

namespace singsing
{

class Thread
{
public:
    Thread();
    ~Thread();
    void start();
    static void threadFunc();
private:
    void run();

private:
    pthread_t id_;
};
}// end singsing
