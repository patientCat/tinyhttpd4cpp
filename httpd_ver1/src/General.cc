//c++ program
//design by >^.^<
//@date    2019-06-03 01:19:31
#include "General.hh"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
namespace General
{
/* 获得一行输出，无论是以\r, \r\n, 还是\n结束。或者以\0结束, 或者输出到buff-1个位置（留一个位置给字符串） */
int get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            if (c == '\r') 
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                if ((n > 0) && (c == '\n')) 
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }// 即将\r\n或者\r转换成\n
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';
    printf(">>>>> test : %s", buf);

    return(i);
}
// 用来查找错误
void 
error_die(const char *sc)
{
    perror(sc);
    exit(1);
}
}
