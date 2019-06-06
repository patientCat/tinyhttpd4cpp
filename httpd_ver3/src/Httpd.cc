/*
 * Tinyhttpd4cpp by jmx
 */

#include "../include/Httpd.hh"
#include "../include/TcpConnection.hh"
#include "../include/Task.hh"
#include "../include/General.hh"
#include "../include/log/Logging.hh"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <stdint.h>

#include <functional>
#include <iostream>


using namespace singsing;
void 
Httpd::loop()
{
    int client_sock = -1;
    while (1) // 只要有一个客户端连接，它就起一个新的线程来处理
    {
        client_sock = listenFd_.accept();
        std::string peername = SocketUtil::getPeerName(client_sock);
        LOG_INFO << ">>> " << peername <<  " is connected";
        Task task;
        pool_.addTask(std::bind(task, client_sock));
    }
}

void
Httpd::startup() // 传入端口号
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGALRM, SIG_IGN);
    
    listenFd_.init();
    listenFd_.setReuseaddr(true);
    listenFd_.bind();
    listenFd_.listen();
    LOG_INFO << "服务器初始化完毕 ";
    LOG_INFO << "httpd running on port: " << listenFd_.getPort();
}

void
Httpd::closeHandle()
{
    ::close(listenFd_.getFd());
}
