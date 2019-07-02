//c++ program
//design by >^.^<
//@date    2019-06-15 01:04:46
#include "InetAddress.hh"

namespace singsing
{

InetAddress::InetAddress(int port, std::string ip)
: port_(port)
, ip_(ip)
{
}

int InetAddress::getPort() const
{
    return port_;
}

std::string
InetAddress::getIp() const
{
    return ip_;
}

bool 
InetAddress::operator==(const InetAddress& rhs)
{
    return port_ == rhs.port_ && ip_ == rhs.ip_;
}

bool 
InetAddress::isAnyIp() const
{
    if(ip_ == "" || ip_ == "0.0.0.0")
    {
        return true;
    }
    return false;
}
std::string 
InetAddress::getStringIpAndPort() const
{
    std::string res;
    if(isAnyIp())
        res = "0.0.0.0";
    else
        res = ip_;
    res += ":";
    res += std::to_string(port_);
    return res;
}
}// end singsing
