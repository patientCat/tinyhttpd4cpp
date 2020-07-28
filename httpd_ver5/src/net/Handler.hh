//c++ program
//design by >^.^<
//@date    2019-06-11 18:27:05
#pragma once

// 想了想生命周期的管理，主要由于俩点，一是对端断开连接后，一是因为超时被Reactor踢掉
#include "Callback.hh"
#include "../base/Noncopyable.hh"

#include <iostream>

//  事件类，目的是用来注册到Reactor中的

namespace singsing{
class Handler : Noncopyable
{
    using ReadCallback = std::function<void(Timestamp)>;
    using Callback = std::function<void()>;
    friend class EpollPoller;
public:
    Handler(int );
    ~Handler();
    void handleEvent();
    void setReadCallback(ReadCallback);
    void setWriteCallback(Callback);
    void setCloseCallback(Callback);
    void enableRead();
    void enableWrite();
    void enableAll();
    void disableRead();
    void disableWrite();
    void disableAll();
    bool isWriting();
    int fd() const{
        return fd_;
    }
    int events() const
    {
        return events_;
    }
    int revents() const
    {
        return revents_;
    }
    void setLen(int len)
    { 
        len_ = len;
    }
    int length()
    {
        return len_;
    }
private:
    const int fd_;
    int events_;
    int revents_;
    bool isInEpoll; // 是否还在epoll的兴趣列表中
    int len_;
    ReadCallback readCallback_;
    Callback writeCallback_;
    Callback closeCallback_;
    Callback errorCallback_;
};
}// end namespace
