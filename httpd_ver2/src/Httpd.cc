/*
 * Tinyhttpd4cpp by jmx
 */

#include "Httpd.hh"
#include "TcpConnection.hh"
#include "Task.hh"
#include "General.hh"

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


void 
Httpd::loop()
{
    int client_sock = -1;
    while (1) // 只要有一个客户端连接，它就起一个新的线程来处理
    {
        client_sock = listenFd_.accept();
        printf("new connection is establinshed\n");
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
    printf("httpd running on port:%d\n", listenFd_.getPort());
}

void
Httpd::closeHandle()
{
    ::close(listenFd_.getFd());
}
