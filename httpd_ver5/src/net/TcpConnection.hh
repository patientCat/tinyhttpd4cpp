#pragma once
#include <stdio.h>

#include "Callback.hh"
#include "Handler.hh"
#include "Buffer.hh"

#include <memory>
#include <boost/noncopyable.hpp>
#include <boost/any.hpp>
#include <atomic>
namespace singsing{



class Reactor;
class TcpConnection
: boost::noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
  enum class ConnectionState
  {
    CONNECTED  = 0,
    DISCONNECTED,
  };
public:
    TcpConnection(Reactor *reactor, int fd);
    ~TcpConnection();
    void registerHandler();
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
    void setCloseCallback(CloseCallback cb)
    {
        closeCallback_ = cb;
    }
    int getFd() const
    {
        return connFd_;
    }

    void send(const void*data, size_t len);
    void send(std::string);
    void send(Buffer* buff);
    void shutdown();

    bool is_connected()
    {
      return conn_state_ == ConnectionState::CONNECTED;
    }

    
    void setObj(const boost::any &obj) 
    {
      obj_ = obj;
    }
    boost::any& getObj()
    {
      return obj_;
    }
private:
    void handleRead(Timestamp timestamp);
    void handleWrite();
    void shutdownInReactor();
private:
    ConnectionState conn_state_{ConnectionState::CONNECTED};

    Reactor *reactor_;
    int connFd_;    
    Handler handler_;
    Buffer inputBuffer_;
    Buffer outputBuffer_;
    ConnectionCallback connectionCallback_;
    MessageCallback messageCallback_;
    WriteCompleteCallback writeCompleteCallback_;
    CloseCallback closeCallback_;
    boost::any obj_;
};
}
