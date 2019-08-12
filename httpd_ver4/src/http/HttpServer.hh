#ifndef __HTTPSERVER_HH__
#define __HTTPSERVER_HH__

// 这是一个简单的webserver，仅仅用来和浏览器交互
// 目前希望做的功能是
// 1. 显示自己的简历

#include "../base/Noncopyable.hh"
#include "../net/TcpServer.hh"

#include <functional>

namespace singsing
{
class HttpRequest;
class HttpResponse;

class HttpServer
: Noncopyable
{
public:
  using HttpCallback = std::function<void (const HttpRequest&, HttpResponse*)>;

public:
  HttpServer(const InetAddress&addr, int threadNum, bool isReusePort = true);
  ~HttpServer() = default;

  void setHttpCallback(HttpCallback cb)
  {
    httpCallback_ = cb;
  }

  void start();
private:
  void onConnection(const TcpConnectionPtr&);
  void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);
  void onRequest(const TcpConnectionPtr&, const HttpRequest&);

  TcpServer server_;
  HttpCallback httpCallback_;
}; 

}// end namespace singsing
#endif
