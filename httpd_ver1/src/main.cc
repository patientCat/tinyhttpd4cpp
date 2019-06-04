//c++ program
//design by >^.^<
//@date    2019-06-02 19:13:53
#include <iostream>
#include "Httpd.hh"
#include "General.hh"

int main(void)
{
    int port = 4000;
    Httpd httpServer(port);
    httpServer.start();
    return 0;
}
