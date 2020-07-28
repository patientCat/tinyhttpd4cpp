#pragma once

#include <string>
namespace singsing{

// 抽象地址，实际上就是端口号+ip地址
class InetAddress
{
public:
    InetAddress(int , std::string ip = "");

    int getPort() const;
    std::string getIp() const;
    std::string getStringIpAndPort() const;
    
    bool isAnyIp() const; // 用来判断是不是0.0.0.0
    bool operator==(const InetAddress& rhs);
private:
    int port_;
    std::string ip_;
};
}//end singsing
