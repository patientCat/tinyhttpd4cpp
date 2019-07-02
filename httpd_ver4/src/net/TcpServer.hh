#pragma once

#include "Socket.hh"
#include "Reactor.hh"
#include "InetAddress.hh"
#include "Callback.hh"
#include "Acceptor.hh"
#include "ReactorThreadPool.hh"

#include <boost/noncopyable.hpp>
#include <map>

// 想想应该有什么组件啊
// 1. 线程池
// 2. Reactor
// 线程池分为主Reactor和其他subReactor。主Reactor负责将任务分发给其他subReactor
// 然后将TcpConnection轮流交给其他subReactor。即subReactor可能对应多个TcpConnection
namespace singsing{


class TcpConnection;
class TcpServer : boost::noncopyable
{
public:
    enum Option{
        kReusePort,
        kNoReusePort
    };
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
public:
    TcpServer(const InetAddress& addr, int num, Option o = kReusePort);
    ~TcpServer();

    void start();

    void newConnection(int);

    void setConnectionCallback(ConnectionCallback cb)
    {
        connectionCallback_ = cb;
    }
    void setMessageCallback(MessageCallback cb)
    {
        messageCallback_ = cb;
    }
    void setWriteCompleteCallback(WriteCompleteCallback cb)
    {
        writeCompleteCallback_ = cb;
    }
public:
    void removeTcpConnection(const TcpConnectionPtr& );
    void removeTcpConnectionInBaseReactor(const TcpConnectionPtr&);
private:
    InetAddress serverAddress_;
    Reactor base_;
    Acceptor acceptor_;
//    Socket listenfd_;
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    int threadNum_;
    ReactorThreadPool threadPool_;
    std::map<int, TcpConnectionPtr> tcpConnectionPtrMap_;
};
} // end singsing
