//c++ program
//design by >^.^<
//@date    2019-06-25 05:19:48
#include <iostream>
#include <thread>
#include <functional>
#include <stdio.h>
#include <chrono>

#include "BlockingQueue.hh"

// 启动俩个线程一个线程向BlockingQueue里面加任务，一个去做任务
using namespace std;
using namespace singsing;

singsing::BlockingQueue<function<void()>> gQueue;

void count()
{
    static int cnt = 1;
    printf("%d\n", cnt++);
}
void threadTask1()
{
    while(1)
    {
    gQueue.put([](){
           printf("hello world\n"); 
           });
    this_thread::sleep_for(chrono::seconds(1)); 
    }
}
void threadTask2()
{
    while(1)
    {
    auto task = gQueue.get();
    task();
    }
}
int main()
{
    thread thread1(threadTask1);
    thread thread3(threadTask2);
    thread thread4(threadTask2);
    thread thread2(threadTask2);
    while(1);    
}
