//c++ program
//design by >^.^<
//@date    2019-06-23 05:01:27
#include <iostream>

#include "../../src/net/TcpServer.hh"
#include "../../src/net/InetAddress.hh"
#include "../../src/net/TcpConnection.hh"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace singsing;
using namespace std;
using namespace placeholders;

// 简单的文件传输服务器
// 就是一次性地直接将文件全部读到内存中，然后发送过去
// 在连接到来的时候，将文件信息全部发送过去

string readFile(const string& filename)
{
    string ret;
    const int kBuffSize = 1024 * 1024;
    int fd = open(filename.c_str(), O_RDONLY);
    if(fd > 0)
    {
        char buff[kBuffSize] = {0};
        int nreads = 0;
        while((nreads = read(fd, buff, sizeof buff)) > 0)
        {
            ret.append(buff, nreads);
        }
    }
    else{
        cout << "open error" << endl;
    } 
    close(fd);
    return ret;
}

class FtpServer
{
public:
    FtpServer(Reactor &reactor, const InetAddress& addr, int num, const string& filename)
    : server_(reactor, addr, num)
    , filename_(filename)
    {
        server_.setConnectionCallback(std::bind(&FtpServer::onConnection, this, _1));
    }
    void onConnection(const TcpConnectionPtr& ptr)
    {
        cout << "connection is established" << endl;
        if(filename_.empty())
        {
            cout << "请输入文件名" << endl;
        }
        else{
            string context = readFile(filename_);

            ptr->send(context);
            ptr->shutdown(); // 连接的主动断开
        } 
    }

    void start()
    {
        server_.start();
    }
private:
    TcpServer server_;
    string filename_;
};

int main(int argc, char **argv)
{
    if(argc > 1)
    {
        string filename(argv[1]);
        InetAddress addr(8888);
        Reactor reactor;
        FtpServer echoServer(reactor, addr, 4, filename);
        echoServer.start();
    }
}
