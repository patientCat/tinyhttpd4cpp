//c++ program
//design by >^.^<
//@date    2019-06-03 00:51:05
#include "../include/TcpConnection.hh"
#include "../include/General.hh"

#include <ctype.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include <stdio.h>

#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define STDIN   0
#define STDOUT  1
#define STDERR  2

namespace singsing{
TcpConnection::~TcpConnection()
{
    close(connFd_);
}

    void
TcpConnection::process()
{
    char buf[1024];
    size_t numchars;
    char method[255];
    char url[255];
    char path[512];
    size_t i, j;
    struct stat st;
    int cgi = 0;      /* becomes true if server decides this is a CGI
                       * program */
    char *query_string = NULL;

    numchars = General::get_line(connFd_, buf, sizeof(buf)); // numchars 为获取到的数据字节数
    i = 0; j = 0;
    while (!ISspace(buf[i]) && (i < sizeof(method) - 1)) // 找到第一个单词
    {
        method[i] = buf[i];
        i++;
    }
    j=i;
    method[i] = '\0'; // method 用来获得第一个指令

    // strcasecmp 忽略大小写比较字符串
    // 这里只实现了GET和POST俩种方法，如果是其他方法，向客户端发送未实现
    if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
    {
        unimplemented();
        return ;
    }

    if (strcasecmp(method, "POST") == 0) // 如果是post方法，就将CGI设置为1
        cgi = 1;

    i = 0;
    while (ISspace(buf[j]) && (j < numchars)) // 跳到下一个单词
        j++;
    while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < numchars)) // method后面接着的应该是url
    {
        url[i] = buf[j];
        i++; j++;
    }
    url[i] = '\0';

    if (strcasecmp(method, "GET") == 0) // 如果method为get, 最终让query_string获得url中？前的字段
    {
        query_string = url;
        while ((*query_string != '?') && (*query_string != '\0'))// 在url里面找问号
            query_string++;
        if (*query_string == '?') // ？代表查询
        {
            cgi = 1;
            *query_string = '\0';
            query_string++;
        }
    }

    sprintf(path, "htdocs%s", url);
    if (path[strlen(path) - 1] == '/')
        strcat(path, "index.html");
    if (stat(path, &st) == -1) {
        while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
            numchars = General::get_line(connFd_, buf, sizeof(buf));
        not_found();
    }
    else
    {
        if ((st.st_mode & S_IFMT) == S_IFDIR)
            strcat(path, "/index.html");
        if ((st.st_mode & S_IXUSR) ||
                (st.st_mode & S_IXGRP) ||
                (st.st_mode & S_IXOTH)    )
            cgi = 1;
        if (!cgi)
        {
            serve_file(path);
        }
        else {
            execute_cgi(path, method, query_string);
        }
    }

    close(connFd_);
}

/**********************************************************************/
/* Inform the connFd_ that a request it has made has a problem.
 * Parameters: connFd_ socket */
/**********************************************************************/
    void 
TcpConnection::bad_request()
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    send(connFd_, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(connFd_, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(connFd_, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(connFd_, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    send(connFd_, buf, sizeof(buf), 0);
}

/**********************************************************************/
/* Put the entire contents of a file out on a socket.  This function
 * is named after the UNIX "cat" command, because it might have been
 * easier just to do something like pipe, fork, and exec("cat").
 * Parameters: the client socket descriptor
 *             FILE pointer for the file to cat */
/**********************************************************************/
    void 
TcpConnection::cat(FILE *resource)
{
    char buf[1024];

    fgets(buf, sizeof(buf), resource);
    while (!feof(resource))
    {
        send(connFd_, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}

/**********************************************************************/
/* Inform the client that a CGI script could not be executed.
 * Parameter: the client socket descriptor. */
/**********************************************************************/
    void 
TcpConnection::cannot_execute()
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
    send(connFd_, buf, strlen(buf), 0);
}
/**********************************************************************/
/* Execute a CGI script.  Will need to set environment variables as
 * appropriate.
 * Parameters: client socket descriptor
 *             path to the CGI script */
/**********************************************************************/
    void 
TcpConnection::execute_cgi(const char *path, const char *method, 
        const char *query_string)
{
    char buf[1024];
    int cgi_output[2];
    int cgi_input[2];
    pid_t pid;
    int status;
    int i;
    char c;
    int numchars = 1;
    int content_length = -1;

    buf[0] = 'A'; buf[1] = '\0';
    if (strcasecmp(method, "GET") == 0)
    {
        while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
            numchars = General::get_line(connFd_, buf, sizeof(buf));
    }
    else if (strcasecmp(method, "POST") == 0) /*POST*/
    {
        numchars = General::get_line(connFd_, buf, sizeof(buf));
        while ((numchars > 0) && strcmp("\n", buf))
        {
            buf[15] = '\0';
            if (strcasecmp(buf, "Content-Length:") == 0)
                content_length = atoi(&(buf[16]));
            numchars = General::get_line(connFd_, buf, sizeof(buf));
        }
        if (content_length == -1) {
            bad_request();
            return;
        }
    }
    else/*HEAD or other*/
    {
    }


    if (pipe(cgi_output) < 0) {
        cannot_execute();
        return;
    }
    if (pipe(cgi_input) < 0) {
        cannot_execute();
        return;
    }

    if ( (pid = fork()) < 0 ) {
        cannot_execute();
        return;
    }
    if (pid == 0)  /* child: CGI script */
    {
        char meth_env[255];
        char query_env[255];
        char length_env[255];

        dup2(cgi_output[1], STDOUT);
        dup2(cgi_input[0], STDIN);
        close(cgi_output[0]);
        close(cgi_input[1]);
        sprintf(meth_env, "REQUEST_METHOD=%s", method);
        putenv(meth_env);
        if (strcasecmp(method, "GET") == 0) {
            sprintf(query_env, "QUERY_STRING=%s", query_string);
            putenv(query_env);
        }
        else {   /* POST */
            sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
            putenv(length_env);
        }
        char * a = NULL;
        execl(path, a);
        exit(0);
    } 
    else {    /* parent */
        close(cgi_output[1]);
        close(cgi_input[0]);
        sprintf(buf, "HTTP/1.0 200 OK\r\n");
        send(connFd_, buf, strlen(buf), 0);
        if (strcasecmp(method, "POST") == 0)
            for (i = 0; i < content_length; i++) {
                recv(connFd_, &c, 1, 0);
                write(cgi_input[1], &c, 1);
            }
        while (read(cgi_output[0], &c, 1) > 0)
            send(connFd_, &c, 1, 0);

        close(cgi_output[0]);
        close(cgi_input[1]);
        waitpid(pid, &status, 0);
    }
}

/**********************************************************************/
/* Return the informational HTTP headers about a file. */
/* Parameters: the socket to print the headers on
 *             the name of the file */
/**********************************************************************/
    void 
TcpConnection::headers(const char *filename)
{
    char buf[1024];
    (void)filename;  /* could use filename to determine file type */

    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    send(connFd_, buf, strlen(buf), 0);
    strcpy(buf, SERVER_STRING);
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(connFd_, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(connFd_, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Give a connFd_ a 404 not found status message. */
/**********************************************************************/
    void 
TcpConnection::not_found()
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(connFd_, buf, strlen(buf), 0);
}
/**********************************************************************/
/* Inform the client that the requested web method has not been
 * implemented.
 * Parameter: the client socket */
/**********************************************************************/
    void 
TcpConnection::unimplemented()
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(connFd_, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(connFd_, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Send a regular file to the client.  Use headers, and report
 * errors to client if they occur.
 * Parameters: a pointer to a file structure produced from the socket
 *              file descriptor
 *             the name of the file to serve */
/**********************************************************************/
    void 
TcpConnection::serve_file(const char *filename)
{
    FILE *resource = NULL;
    int numchars = 1;
    char buf[1024];

    buf[0] = 'A'; buf[1] = '\0';
    while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
        numchars = General::get_line(connFd_, buf, sizeof(buf));

    resource = fopen(filename, "r");
    if (resource == NULL)
        not_found();
    else
    {
        headers(filename);
        cat(resource);
    }
    fclose(resource);
}
}
