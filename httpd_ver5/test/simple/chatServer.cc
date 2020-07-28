//c++ program
//design by >^.^<
//@date    2019-06-23 05:01:27
#include <iostream>

#include "../../src/net/TcpServer.hh"
#include "../../src/net/InetAddress.hh"
#include "../../src/net/TcpConnection.hh"

using namespace singsing;
using namespace std;
using namespace placeholders;

class ChatServer
{
public:
    ChatServer(Reactor& reactor, const InetAddress& addr, int num)
    : server_(reactor, addr, num)
    {
        server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
        server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    }
    void onConnection(const TcpConnectionPtr& ptr)
    {
        cout << "fd = " << ptr->getFd() << endl;
        cout << "connection is established" << endl;
        connectionPtrList_.push_back(ptr);
    }

    void onMessage(const TcpConnectionPtr& ptr, Buffer* buffer, Timestamp when)
    {
        // 收到消息后，发送给除了自己以外的所有人
        std::string receive = buffer->returnAllStringAndUpdate();
        for(auto everyone : connectionPtrList_)
        {
            if(everyone->getFd() != ptr->getFd())
                everyone->send(receive);
        }
    }
    void start()
    {
        server_.start();
    }
private:
    TcpServer server_;
    std::vector<shared_ptr<TcpConnection>> connectionPtrList_;  
};

int main()
{
    InetAddress addr(8888);
    Reactor reactor;
    ChatServer echoServer(reactor, addr, 4);
    echoServer.start();
}
