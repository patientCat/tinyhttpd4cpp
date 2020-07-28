
#ifndef __SimpleTimeWheel__
#define __SimpleTimeWheel__


// 用于muduo的简单时间轮
#include "boost/circular_buffer.hpp"

#include <unordered_set>

template <class T >
class SimpleTimeWheel
{
  public:

    SimpleTimeWheel()
      : buffer_(8)
    {

    }
    void resize(size_t N)
    {
      buffer_.resize(N);
    }

    std::unordered_set<T>& getLastBucket()
    {
      return buffer_.back();
    }

    void printBuffer()
    {
    }
    void tick()
    {
      buffer_.push_back(std::unordered_set<T> {});
    }
  private:
    
    boost::circular_buffer<std::unordered_set<T>> buffer_;
};
#endif
