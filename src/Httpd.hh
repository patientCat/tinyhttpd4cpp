#ifndef __HTTPD_HH__
#define __HTTPD_HH__


#include "Socket.hh"
#include <string>

using std::string;
class Httpd
{
public:
    Httpd(int port, const string& ip = "")
    : listenFd_(port, ip)
    {
    }
    void start()
    {
        startup();
        loop();
        closeHandle(); 
    }

    int getFd()const;

private:
    void startup();
    void loop();
    void taskHandle(int);
    void closeHandle();

    static void* accept_request(void *);
private:
    Socket listenFd_;
};
#endif
