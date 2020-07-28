//
// Created by Pawn on 2020/7/23.
//

#ifndef HTTPROUTER_HTTPROUTERERROR_H
#define HTTPROUTER_HTTPROUTERERROR_H

#include <exception>
#include <stdexcept>

// 一些自定义异常

#include <string>

class HttpRouterError : public std::exception
{
public:
     HttpRouterError(const std::string& error)
    : error_(error)
    {

    }

    const char *what() const throw() override {
        return error_.c_str();
    }

private:
    std::string error_;
};

class HttpRouter_RouteNotFound : public HttpRouterError
{
public:
    HttpRouter_RouteNotFound(const std:: string& error)
    : HttpRouterError(error)
    {

    }
};

class HttpRouter_NoHandler : public HttpRouterError
{
public:
    HttpRouter_NoHandler(const std:: string& error)
            : HttpRouterError(error)
    {

    }
};

class HttpRouter_InvalidArg : public HttpRouterError
{
public:
    explicit HttpRouter_InvalidArg(const std::string &error)
    : HttpRouterError(error)
    {

    }
};

#endif //HTTPROUTER_HTTPROUTERERROR_H

