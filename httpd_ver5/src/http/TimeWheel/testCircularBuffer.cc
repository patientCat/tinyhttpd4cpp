//c++ program
//design by >^.^<
//@date    2020-07-28 04:58:08
#include <iostream>
#include "boost/circular_buffer.hpp"
#include <vector>


using namespace std;

class Entry
{
  public:
    Entry() 
    {
      cout << "construct" << endl;
    }
    
    ~Entry()
    {
      cout << "析构" << endl;
    }
};
int main()
{
  using namespace boost; 
  Entry x1;
  vector<Entry> evec;
  evec.push_back(x1);
  evec.push_back(x1);
  evec.push_back(x1);
  evec.push_back(x1);
  evec = vector<Entry> {};
  while(1);
}
