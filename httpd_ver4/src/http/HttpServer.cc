//c++ program
//design by >^.^<
//@date    2019-08-11 19:33:58
#include "HttpServer.hh"
#include "HttpContext.hh"
#include "HttpRequest.hh"
#include "HttpResponse.hh"
#include "../base/Logging.hh"
#include "../net/TcpConnection.hh"

#include <string>
#include <functional>

using namespace std;
using namespace singsing;
using namespace placeholders;

namespace detail
{
void defaultHttpCallback(const HttpRequest&, HttpResponse* resp)
{
  resp->setStatusCode(HttpResponse::k404NotFound);
  resp->setStatusMessage("Not Found");
  resp->setCloseConnection(true);
}
}

HttpServer::HttpServer(const InetAddress& addr, int threadNum, bool isReusePort)
  : server_(addr, threadNum, isReusePort ? TcpServer::kReusePort : TcpServer::kNoReusePort)
{
  server_.setConnectionCallback(bind(&HttpServer::onConnection, this, _1));
  server_.setMessageCallback(bind(&HttpServer::onMessage, this, _1, _2, _3));
}

void
HttpServer::start()
{
  LOG_WARN << "HttpServer starts listenning";
  server_.start();
}

void 
HttpServer::onConnection(const TcpConnectionPtr &conn)
{
  conn->setObj(static_cast<void*>(new HttpContext));
}

void 
HttpServer::onMessage(const TcpConnectionPtr& conn, Buffer*buf, Timestamp receiveTime)
{
  auto context = static_cast<HttpContext*>(conn->getObj());
  if(!context->parseRequest(buf, receiveTime))
  {
    conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
    conn->shutdown();
  }
  if (context->isGotAll())
  {
    onRequest(conn, context->request());
    context->reset();
  }
}

void 
HttpServer::onRequest(const TcpConnectionPtr& conn, const HttpRequest& req)
{
  const string& connection = req.getHeader("Connection");
  bool close = connection == "close" || 
    (req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");
  HttpResponse response(close);
  httpCallback_(req, &response);
  Buffer buf;
  response.appendToBuffer(&buf);
  conn->send(&buf);
  if(response.closeConnection())
  {
    conn->shutdown();
  }
}
