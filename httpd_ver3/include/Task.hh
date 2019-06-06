#pragma once

#include "TcpConnection.hh"
namespace singsing{
class Task
{
public:
    void operator()(int fd)
    {
        TcpConnection conn(fd);
        conn.process();
    }

private:
    int fd_;
};
}
