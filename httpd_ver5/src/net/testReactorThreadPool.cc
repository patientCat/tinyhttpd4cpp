//c++ program
//design by >^.^<
//@date    2019-06-25 06:32:34
#include "ReactorThreadPool.hh"
#include "Reactor.hh"

#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

using namespace std;
using namespace singsing;

ReactorThreadPool threadpool(4);

class Test
{
public:
    void print()
    {
            printf("hello\n");
    }
};
void doTask()
{
    while(1)
    {
    Reactor * loop = threadpool.getNextLoop();
    Test a;
    loop->addTask(
            bind(&Test::print, &a)
            );
    this_thread::sleep_for(chrono::seconds(1));
    }
}
int main()
{
    threadpool.start();
    thread thread1(doTask);
    while(1);
}
