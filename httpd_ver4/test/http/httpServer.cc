//c++ program
//design by >^.^<
//@date    2019-08-12 02:31:50
#include <iostream>
#include "../../src/http/HttpServer.hh"
#include "../../src/http/HttpRequest.hh"
#include "../../src/http/HttpResponse.hh"
#include "../../src/net/InetAddress.hh"

#include <string>
#include <stdio.h>

using namespace singsing;
using namespace std;


// 这里很简单，就是读取path，然后再将path打开，添加到body中即可

void httpCb(const HttpRequest& req, HttpResponse *resp)
{
  if(req.path() != "/index.html"){ // not found
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("404 not found");
    resp->setCloseConnection(true);
    return;
  }

  // 在文件名中，滤除/符号
  string filename = req.path().substr(1);  
  
  FILE* fp = fopen(filename.c_str(), "rb");
  if(!fp) 
  {
    resp->setStatusCode(HttpResponse::k400BadRequest);
    resp->setStatusMessage(filename + " can't find");
    resp->setCloseConnection(true);
    return;
  }

  fseek(fp, 0, SEEK_END);
  int fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *body = new char[fileSize+1];

  fread(body, 1, fileSize, fp);
  resp->setStatusCode(HttpResponse::k200Ok);
  resp->setStatusMessage("OK");
  resp->setContentType("text/html");
  resp->setBody(body);
}

int main()
{
  InetAddress addr(8888);
  HttpServer httpd(addr, 4); 
  httpd.setHttpCallback(httpCb); 
  httpd.start();
}
