#ifndef __HTTPSERVER_HH__
#define __HTTPSERVER_HH__

// 这是一个简单的webserver，仅仅用来和浏览器交互
// 目前希望做的功能是
// 1. 显示自己的简历

#include "../base/Noncopyable.hh"
#include "../net/TcpServer.hh"
#include "HttpRouter/HttpRouter.hh"
#include "./TimeWheel/SimpleTimeWheel.hh"
#include "../net/TcpConnection.hh"

#include <functional>

namespace singsing
{
class HttpRequest;
class HttpResponse;


// 必须持有weak_ptr，如果持有shared_ptr，客户端主动断开时，会有问题
class IdleEntry
{
  public:
    IdleEntry(const std::weak_ptr<TcpConnection> &weakConn)
      : weakConnection_(weakConn)
    {
    }
    ~IdleEntry()
    {
      auto conn = weakConnection_.lock();
      if(conn)
        conn->shutdown();
    }
  private:
    std::weak_ptr<TcpConnection> weakConnection_;
};

using IdleEntryPtr = std::shared_ptr<IdleEntry>;
using WeakIdleEntryPtr = std::weak_ptr<IdleEntry>;

class HttpServer
: Noncopyable
{
public:
  using HttpCallback = std::function<void (const HttpRequest&, HttpResponse*)>;

public:
  HttpServer(const InetAddress&addr, int threadNum, bool isReusePort = true);
  ~HttpServer() = default;

  void setHttpRouter(HttpRouter * router)
  {
    up_router_.reset(router);
  }

  // 开启时间轮踢掉空闲连接
  // size 即是时间轮大小，也是空闲连接持续时间s
  void setIdleConnectionOut(size_t size)
  {
    simple_time_wheel_.resize(size);
    is_idleconnection_out_ = true;
    reactor_.runTaskAfter(std::bind(&SimpleTimeWheel<IdleEntryPtr>::tick, &simple_time_wheel_), size * 1000);
  }

  void start();
private:
  void setHttpCallback(HttpCallback cb)
  {
    httpCallback_ = cb;
  }

  void onConnection(const TcpConnectionPtr&);
  void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);
  void onRequest(const TcpConnectionPtr&, const HttpRequest&);

  Reactor reactor_;

  TcpServer server_;
  HttpCallback httpCallback_;
  bool is_idleconnection_out_{false};

  SimpleTimeWheel<IdleEntryPtr> simple_time_wheel_;

  std::weak_ptr<TcpConnection> curr_weak_connection_;
  std::unique_ptr<HttpRouter> up_router_;
}; 

}// end namespace singsing
#endif
