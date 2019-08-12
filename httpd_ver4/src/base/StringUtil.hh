# pragma once

#include <ctype.h>

namespace singsing
{

class StringUtil
{
public:

  static const char *SkipWhiteSpace(const char*p)
  {
    if(!p && !*p)
      return nullptr;
    while(p && isspace(*p))
    {
      p++; 
    }
    return p;
  }
  static char* SkipWhiteSpace(char *p)
  {
    return const_cast<char*>(SkipWhiteSpace(const_cast<const char*>(p)));
  }
};

}
