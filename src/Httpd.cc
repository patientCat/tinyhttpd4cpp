/*
 * Tinyhttpd4cpp by jmx
 */

#include "Httpd.hh"
#include "TcpConnection.hh"

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
    pthread_t newthread;
    int client_sock = -1;
    while (1) // 只要有一个客户端连接，它就起一个新的线程来处理
    {
        client_sock = listenFd_.accept();
        printf("new connection is establinshed\n");
        if (pthread_create( &newthread, NULL, accept_request,
                    (void *)(reinterpret_cast<int*>(client_sock))))
            perror("pthread_create");
    }
}

/**********************************************************************/
/* A request has caused a call to accept() on the server port to
 * return.  Process the request appropriately.
 * Parameters: the socket connected to the client */
/**********************************************************************/
// 这里是静态函数，现在想让其去执行Httpd类的动态成员函数
// 1. 将其它全部设置为静态
// 2. 传入指针
void* 
Httpd::accept_request(void *arg)
{
    int client = (reinterpret_cast<long>(arg));
    TcpConnection conn(client);
    conn.process();
    pthread_exit(NULL);
}


/**********************************************************************/
/* This function starts the process of listening for web connections
 * on a specified port.  If the port is 0, then dynamically allocate a
 * port and modify the original port variable to reflect the actual
 * port.
 * Parameters: pointer to variable containing the port to connect on
 * Returns: the socket */
/**********************************************************************/
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


/**********************************************************************/

void
Httpd::closeHandle()
{
    ::close(listenFd_.getFd());
}
