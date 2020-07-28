//c++ program
//design by >^.^<
//@date    2019-06-25 06:00:19
#include <iostream>
#include <thread>
#include <chrono>
#include "Reactor.hh"
#include <stdio.h>
#include "../base/Logging.hh"

using namespace std;
using namespace singsing;
Reactor reactor;

void doTask()
{
    while(1)
    {
    reactor.addTask([](){
            printf("hello\n");
            });
    this_thread::sleep_for(chrono::seconds(2));
    }
}
int main()
{
    Logger::setLogLevel(Logger::LogLevel::DEBUG);    
    thread thread1(doTask);
    reactor.loop();
}
