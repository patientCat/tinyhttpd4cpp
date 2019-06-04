//c++ program
//design by >^.^<
//@date    2019-06-02 19:31:31

#include "Socket.hh"
#include "General.hh"

#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

Socket::Socket(int port, const std::string& ip)
: port_(port)
, ip_(ip)
{
    fd_ = -1;
} void

Socket::init()
{
    printf("socket\n");
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_ < 0)
        General::error_die(">>> socket error:");
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port_);
    if(ip_ == "")
    {
        printf("localhost\n");
        addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else{
        inet_aton(ip_.c_str(), &addr_.sin_addr);
    }
}
void 
Socket::bind()
{
    printf("bind\n");
    assert(fd_ != -1);
    int ret = ::bind(fd_, reinterpret_cast<sockaddr*>(&addr_), sizeof(addr_));
    if(ret < 0)
        General::error_die(">>> bind error:");
}
void 
Socket::listen()
{
    printf("listen\n");
    assert(fd_ != -1);
    int ret = ::listen(fd_, 5);
    if(ret < 0)
        General::error_die(">>> listen error:");
}
int 
Socket::accept()
{
    printf("accept\n");
    assert(fd_ != -1);
    int acceptFd = ::accept(fd_, NULL, NULL);
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
std::string 
Socket::getIpAstring() const
{
    return ip_;
}
int 
Socket::getPort() const
{
    return port_;
}
void
Socket::setReuseaddr(bool on = false)
{
    assert(fd_ != -1);
    int one = on;
    if ((setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one))) < 0)  // 开启端口复用
    {  
        General::error_die(">>> setsockopt failed");
    }
}
