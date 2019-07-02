#pragma once

#include "../base/Timestamp.hh"
#include "Callback.hh"

#include <stdint.h>
#include <functional>


namespace singsing{
class Timer
{
public:
    Timer(const TimerCallback &cb, const Timestamp& when)
    : callback_(cb)
    , when_(when)
    {}
    void run() const {  callback_();    }
    Timestamp getExpTime() const {
        return when_;
    }
private:
    const TimerCallback callback_;
    Timestamp when_;
};
}// end singsing
