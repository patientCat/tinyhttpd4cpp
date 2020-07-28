//c++ program
//design by >^.^<
//@date    2020-07-25 01:12:47
#include <iostream>

#include <iostream>

#include "HttpRouter.hh"

using namespace  std;
void sayHello()
{
    cout << "hello" << endl;
}

void index_handler()
{
    cout << "index" << endl;
}

void match_wildcard_node()
{
    cout << "match wildcard node" << endl;
}

int main() {
    HttpRouter router;
    router.register_handler("/", index_handler);
    router.register_handler("/static/*", match_wildcard_node);
    router.handle("/to_match/wildcard_node");
    return 0;
}

