#ifndef __HTTPD_HH__
#define __HTTPD_HH__


#include "Socket.hh"
#include "ThreadPool.hh"

#include <string>

using std::string;
class Httpd
{
public:
    Httpd(int port, const string& ip = "", int threadNums = 4)
    : listenFd_(port, ip)
    , pool_(threadNums)
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
    ThreadPool pool_;
};
#endif
