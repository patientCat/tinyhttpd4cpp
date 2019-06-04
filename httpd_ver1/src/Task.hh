#pragma once

#include "TcpConnection.hh"
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
