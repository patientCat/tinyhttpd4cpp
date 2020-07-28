#pragma once

#include "InetAddress.hh"
#include "Socket.hh"
#include "Callback.hh"
#include "Handler.hh"


namespace singsing
{

// Acceptor抽象的目的：
// 1. 完成服务器sfd的listen
// 2. 向base注册listenfd
// 3. 正确设置connection的回调函数
class Reactor;
class Acceptor
{
    using Callback = std::function<void(int)>;
public:
    Acceptor(const InetAddress& addr, Reactor* base, bool reusePort);
    ~Acceptor();
    void handleRead();
    void setConnectionCallback(Callback cb)
    {  connectionCallback_ = cb; }

private:
    Socket acceptSocket_;
    Callback connectionCallback_;
    Reactor *base_;
    Handler acceptHandler_;
    int idleFd_;
};
}//end singsing
