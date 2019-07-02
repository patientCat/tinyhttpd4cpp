//c++ program
//design by >^.^<
//@date    2019-06-02 19:31:31

#include "Socket.hh"
#include "../base/General.hh"

#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

namespace singsing{
namespace SocketUtil{
std::string getPeerName(int fd)
{
    sockaddr_in addr;
    getpeername(fd, (sockaddr*)&addr, NULL);
    std::string ret(inet_ntoa(addr.sin_addr));
    return ret;
}
void shutdownWrite(int fd)
{
    ::shutdown(fd, SHUT_WR);
}

}// end SocketUtil


Socket::Socket(const InetAddress& addr)
: addr_(addr)
{
    initOrDie();
} 



void
Socket::initOrDie()
{
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ < 0)
        General::error_die(">>> socket error:");
    bzero(&sockaddr_, sizeof(addr_));
    sockaddr_.sin_family = AF_INET;
    sockaddr_.sin_port = htons(addr_.getPort());
    if(addr_.isAnyIp())
    {
        sockaddr_.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else{
        inet_aton(addr_.getIp().c_str(), &sockaddr_.sin_addr);
    }
}
void 
Socket::bindOrDie()
{
    assert(fd_ != -1);
    int ret = ::bind(fd_, reinterpret_cast<sockaddr*>(&sockaddr_), sizeof(sockaddr_));
    if(ret < 0)
        General::error_die(">>> bind error:");
}
void 
Socket::listenOrDie()
{
    assert(fd_ != -1);
    int ret = ::listen(fd_, 5);
    if(ret < 0)
        General::error_die(">>> listen error:");
}
int 
Socket::acceptOrDie()
{
    assert(fd_ != -1);
    int acceptFd = ::accept4(fd_, NULL, NULL, O_NONBLOCK);
    if(acceptFd < 0)
        General::error_die(">>> accept error:");
    return acceptFd;
}
Socket::~Socket()
{
    close(fd_);
}
int 
Socket::getFd() const
{
    return fd_;
}

InetAddress 
Socket::getInetAddress() const
{
    return addr_;
}

void
Socket::setReuseaddr(bool on = false)
{
    assert(fd_ != -1);
    int one = on;
    if ((setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one))) < 0)  // 开启端口复用
    {  
        General::error_die(">>> setsockopt reuse failed");
    }
}
void 
Socket::setNonBlock()
{
    int old_option = fcntl(fd_, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    if(fcntl(fd_, F_SETFL, new_option) < 0)
    {
        General::error_die(">>> setsockopt nonblock failed");
    }
}
} // end singsing
