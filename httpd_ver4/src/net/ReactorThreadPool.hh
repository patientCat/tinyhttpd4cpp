#pragma once

/*
 * 设计指导
 * ReactorThreadPool，线程池，每个线程池将运行一个Reactor。每个Reactor将负责多个TcpConnection
 * 每个Reactor有自己的工作流程
 * 如何把一个TcpConnection交给一个subReactor呢？
 * 我们先来看subReactor的工作逻辑
 * 首先subReactor是自己一个人工作在一个独立的线程中的。
 * while(1)
 * {
 *   activeEventsList = poller::poll();
 *   for(auto event : activeEventsList)
 *     event.handleEvent();
 *   handleTask();
 * }
 * 我们需要保证的是TcpConnection的connectionEstablished是工作在自己attach的subReactor中的。然后我们就可以在
 * connectionEstablished中注册connfd的event。当event事件发生的时候，也只会被自己attach的subReactor所调用
 */

#include <vector>
#include <memory>

#include "ReactorThread.hh"

namespace  singsing{

class Reactor;
class ReactorThreadPool
{
public:
    ReactorThreadPool(int nums);
    //void setThreadNums(int);
    void start();
    // 通过这个接口获得一个subReactor的指针，然后就可以向里面添加任务了
    Reactor* getNextLoop();
private:
    int threadNums_;
    std::vector<std::unique_ptr<ReactorThread>> threads_;
    std::vector<Reactor*> reactorPtrList_;
    int next_;
    bool isStarting_;
};
}// end singsing
