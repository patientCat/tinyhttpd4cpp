//c++ program
//design by >^.^<
//@date    2019-06-23 05:01:27
#include <iostream>

#include "../src/net/TcpServer.hh"
#include "../src/net/InetAddress.hh"
#include "../src/net/TcpConnection.hh"

using namespace singsing;
using namespace std;
using namespace placeholders;

class EchoServer
{
public:
    EchoServer(const InetAddress& addr, int num)
    : server_(addr, num)
    {
        server_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, _1));
        server_.setMessageCallback(std::bind(&EchoServer::onMessage, this, _1, _2, _3));
    }
    void onConnection(const TcpConnectionPtr& ptr)
    {
        cout << "connection is established" << endl;
    }

    void onMessage(const TcpConnectionPtr& ptr, Buffer* buffer, Timestamp when)
    {
        std::string receive = buffer->returnAllStringAndUpdate();
        ptr->send(receive);
    }
    void start()
    {
        server_.start();
    }
private:
    TcpServer server_;
};

int main()
{
    InetAddress addr(8888);
    EchoServer echoServer(addr, 4);
    echoServer.start();
}
