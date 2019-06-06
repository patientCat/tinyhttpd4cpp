#pragma once
#include <stdio.h>
namespace singsing{

class TcpConnection
{
public:
    TcpConnection(int fd) : connFd_(fd){}
    void process();
    void cat(FILE *resource);
    ~TcpConnection();
private:
    void bad_request();
    void cannot_execute();
    void execute_cgi(const char *path, const char *method, const char *query_string);
    void not_found();
    void headers(const char *filename);
    void unimplemented();
    void serve_file(const char *filename);
    int connFd_;    
};
}
