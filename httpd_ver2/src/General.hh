#ifndef __GENERAL_HH__
#define __GENERAL_HH__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
namespace General
{
/* 获得一行输出，无论是以\r, \r\n, 还是\n结束。或者以\0结束, 或者输出到buff-1个位置（留一个位置给字符串） */
int get_line(int sock, char *buf, int size);

// 用来查找错误
void error_die(const char *sc);
}
#endif
