//c++ program
//design by >^.^<
//@date    2019-08-11 20:16:07
#include "../net/Buffer.hh"
#include "../base/StringUtil.hh"
#include "HttpContext.hh"

#include <algorithm>

using namespace singsing;

namespace {
const int kCrLfLen = 2;
const int kHttpVersionLen = 8;
}

// 解析请求行
// 请求行一般为 GET / HTTP/1.1类似这样的形式
bool HttpContext::processRequestLine(const char* begin, const char* end)
{
  bool isSucceed = false;
  const char* start = begin;
  // 设置method
  const char* space = std::find(start, end, ' ');
  if (space != end && request_.setMethod(start, space))
  {
    start = StringUtil::SkipWhiteSpace(space);
    // 设置path，如果有query的，设置query
    space = std::find(start, end, ' ');
    if (space != end)
    {
      const char* question = std::find(start, space, '?');
      if (question != space)
      {
        request_.setPath(start, question);
        request_.setQuery(question, space);
      }
      else
      {
        request_.setPath(start, space);
      }
      start = StringUtil::SkipWhiteSpace(space);
      // 版本1.0和1.1都接收
      isSucceed = end-start == kHttpVersionLen && std::equal(start, end-1, "HTTP/1.");
      if (isSucceed)
      {
        if (*(end-1) == '1')
        {
          request_.setVersion(HttpRequest::kHttp11);
        }
        else if (*(end-1) == '0')
        {
          request_.setVersion(HttpRequest::kHttp10);
        }
        else
        {
          isSucceed = false;
        }
      }
    }
  }
  return isSucceed;
}


// return false if any error
// 利用状态机编程，
// 1. 当解析某个状态时，就取出这行的数据，即找到\r\n，如果没有则失败
// 状态不会发生变化，当下次解析时候，依然是这个状态
// 2. 找到了\r\n，读取了这行数据，但是因为格式错误，解析失败，状态依然不发生变化
// 3. 找到了\r\n，成功读取数据，成功解析，状态发生变化，下次就会进入下一个状态的解析
// 4. 当解析完一个Request请求之后，状态会变为gotAll，调用者通过这个状态可以去返回Response消息
bool HttpContext::parseRequest(Buffer* buf, Timestamp receiveTime)
{
  bool ok = true;
  bool hasMore = true;
  while (hasMore)
  {
    if (state_ == kExpectRequestLine)
    {
      const char* crlf = buf->findCRLF();
      if (crlf)
      {
        ok = processRequestLine(buf->readIndexPtr(), crlf);
        if (ok)
        {
          request_.setReceiveTime(receiveTime);
          buf->updateReadIndexUntil(crlf + kCrLfLen);
          state_ = kExpectHeaders;
        }
        else
        {
          hasMore = false;
        }
      }
      else
      {
        hasMore = false;
      }
    }
    else if (state_ == kExpectHeaders)
    {
      const char* crlf = buf->findCRLF();
      if (crlf)
      {
        const char* start = buf->readIndexPtr();
        const char* colon = std::find(start, crlf, ':');
        if (colon != crlf)
        {
          request_.addHeader(buf->readIndexPtr(), colon, crlf);
        }
        else
        {
          // empty line, end of header
          // FIXME:
          state_ = kGotAll;
          hasMore = false;
        }
        buf->updateReadIndexUntil(crlf + kCrLfLen);
      }
      else
      {
        hasMore = false;
      }
    }
    else if (state_ == kExpectBody)
    {
      // FIXME:
    }
  }
  return ok;
}

