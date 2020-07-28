//c++ program
//design by >^.^<
//@date    2020-07-28 06:06:47
#include <iostream>
#include <boost/any.hpp>

using namespace std;
int main()
{
  int * x = new int(10);
  boost::any obj = x;
  int * y = boost::any_cast<int*> (obj);
  cout << *y << endl;
}
