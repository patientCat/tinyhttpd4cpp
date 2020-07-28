//
// Created by Pawn on 2020/7/23.
//

#ifndef HTTPROUTER_HTTPROUTER_H
#define HTTPROUTER_HTTPROUTER_H

// 模仿go httprouter实现的一个http中间件

// 1. 分为四种方法来注册路由 当前只实现get post put

#include "PrefixTree.hh"
#include "HttpRouterError.hh"
#include "HttpHandler.hh"
#include "../HttpRequest.hh"
#include "../HttpResponse.hh"
#include "../../base/Logging.hh"

#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>

namespace detail{

  inline  void default_route(const HttpRequest &req, HttpResponse *resp)
  {  
      // 找不到路由时候的错误处理
    std::cout << "404" << std::endl;
      resp->setStatusCode(HttpResponse::k404NotFound);
      resp->setStatusMessage("404 not found");
      resp->setCloseConnection(true);
  }

}
namespace singsing{


class HttpRouter {
public:
    HttpRouter()
    {
      register_default_handler(::detail::default_route);
    }

    void register_handler(const std::string &url, const HttpHandler& handler)
    {
        if(url.empty() || url[0] != '/')
            throw HttpRouter_InvalidArg("路由不合法");

        // 路由注册
        prefixTree.add_route(url, handler);
    }
    // 当前先不考虑正则匹配的问题，
    void handle(const std::string &url, const HttpRequest& req, HttpResponse *response)
    {
        try{
            auto handler = get_handler(url);
            handler(req, response);
        }
        catch (HttpRouter_NoHandler &e) {

            std::cout << e.what() << std::endl;
            std::cout << "没有可用的handler" << std::endl; // log is comment;
            if(defaultHandler)
                defaultHandler(req, response);
        }
    }
    void register_default_handler(const HttpHandler& handler)
    {
        defaultHandler = handler;
    }

private:
    HttpHandler get_handler(const std::string& str)
    {
        auto handler = prefixTree.search(str);
        return handler;
    }
    PrefixTree prefixTree;

    HttpHandler defaultHandler;
};

}

#endif //HTTPROUTER_HTTPROUTER_H

