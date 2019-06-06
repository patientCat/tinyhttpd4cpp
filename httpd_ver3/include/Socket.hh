#ifndef __SOCKET_HH__
#define __SOCKET_HH__

#include <string>
#include "arpa/inet.h"
#include <boost/noncopyable.hpp>

namespace singsing{

namespace SocketUtil{
    std::string getPeerName(int fd);
}
class Socket
: boost::noncopyable
{
public:
    Socket(int port, const std::string& ip = "");
    ~Socket();
    int getFd() const;
    std::string getIpAstring() const;
    int getPort() const;

    void init();
    void bind();
    void listen();
    void setReuseaddr(bool);
    int accept();
private:
    int port_;
    std::string ip_;
    int fd_;
    sockaddr_in addr_;
};
#endif
}
