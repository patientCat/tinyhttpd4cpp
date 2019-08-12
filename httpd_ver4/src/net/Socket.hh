#pragma once
#include "../base/Noncopyable.hh"
#include "InetAddress.hh"

#include <arpa/inet.h>

#include <string>
namespace singsing{

namespace SocketUtil{
    std::string getPeerName(int fd);
    // 半关闭
    void shutdownWrite(int fd);
}
class Socket
: Noncopyable
{
public:
    Socket(const InetAddress& addr);
    ~Socket();
    int getFd() const;
    InetAddress getInetAddress() const;

    void startToListen()
    {
        bindOrDie();
        listenOrDie();
    }
    void initOrDie();
    void bindOrDie();
    void listenOrDie();
    void setNonBlock();
    void setReuseaddr(bool);
    int acceptOrDie();
private:
    InetAddress addr_;
    int fd_;
    sockaddr_in sockaddr_;
};
} // end singsing
