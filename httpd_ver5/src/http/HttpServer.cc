//c++ program
//design by >^.^<
//@date    2019-08-11 19:33:58
#include "HttpServer.hh"
#include "HttpContext.hh"
#include "HttpRequest.hh"
#include "HttpResponse.hh"
#include "../base/Logging.hh"
#include "../net/TcpConnection.hh"
#include "HttpRouter/HttpRouter.hh"
#include <tuple>
#include "./TimeWheel/SimpleTimeWheel.hh"

#include <string>
#include <functional>

using namespace std;
using namespace singsing;
using namespace placeholders;

using ConextType = tuple<shared_ptr<HttpContext>, weak_ptr<IdleEntry>>;

namespace detail
{
void defaultHttpCallback(const HttpRequest&, HttpResponse* resp)
{
  resp->setStatusCode(HttpResponse::k404NotFound);
  resp->setStatusMessage("Not Found");
  resp->setCloseConnection(true);
}

inline HttpRouter* defaultHttpRouter() // 这里会尾优化，不用担心性能
{
    HttpRouter *router = new HttpRouter;
    return router;
}
}


HttpServer::HttpServer(const InetAddress& addr, int threadNum, bool isReusePort)
  : reactor_()
  , server_(reactor_, addr, threadNum, isReusePort ? TcpServer::kReusePort : TcpServer::kNoReusePort)
{
  server_.setConnectionCallback(bind(&HttpServer::onConnection, this, _1));
  server_.setMessageCallback(bind(&HttpServer::onMessage, this, _1, _2, _3));
  up_router_.reset(::detail::defaultHttpRouter());
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
  if(conn->is_connected())
  {
    IdleEntryPtr ep (new IdleEntry(conn));
    simple_time_wheel_.getLastBucket().insert(ep);

    tuple<shared_ptr<HttpContext>, weak_ptr<IdleEntry>> context(shared_ptr<HttpContext>(new HttpContext), ep);
    conn->setObj(context);

  }else{
  }
}

void 
HttpServer::onMessage(const TcpConnectionPtr& conn, Buffer*buf, Timestamp receiveTime)
{
  LOG_TRACE << "http onMessage ";
  auto context = boost::any_cast<ConextType>(conn->getObj());

  auto http_context = std::get<0>(context);
  if(!http_context->parseRequest(buf, receiveTime))
  {
    conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
    conn->shutdown();
  }
  if (http_context->isGotAll())
  {
    onRequest(conn, http_context->request());
    http_context->reset();
  }
  WeakIdleEntryPtr weak_idle_entry = std::get<1>(context);
  IdleEntryPtr ep( weak_idle_entry.lock());
  if(ep)
  {
    simple_time_wheel_.getLastBucket().insert(ep);
  }
}

void 
HttpServer::onRequest(const TcpConnectionPtr& conn, const HttpRequest& req)
{
  LOG_TRACE << "http onRequest ";
  const string& connection = req.getHeader("Connection");
  bool close = connection == "close" || 
    (req.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");

  std::string path = req.path();
  LOG_TRACE << "path = " << path ;


  HttpResponse response(close);

  up_router_->handle(path, req, &response);

  // httpCallback_(req, &response);
  Buffer buf;
  response.appendToBuffer(&buf);
  conn->send(&buf);

  if(response.closeConnection())
  {
    conn->shutdown();
  }
}
