#pragma once


#include <sys/timerfd.h>
#include "../base/Logging.hh"

namespace singsing
{
namespace timerfdops
{
int createTimerfdOrDie()
{
    int retfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
    if(retfd < 0)
        LOG_ERROR << "timerfd_create";
    return retfd;
}

int setTimer(int fd, Timestamp initval, Timestamp interval)
{
    int ret = timerfd_settime(fd, );
}

} // end timerfd
} // end singsing
