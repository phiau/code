//
// Created by zhenbiao.cai on 2016/12/2.
//

#ifndef LIBEVENT_PTIMEUTILS_H
#define LIBEVENT_PTIMEUTILS_H

#include <time.h>
#include "pstddef.h"

long p_now() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000 + now.tv_usec/1000;
}

#endif //LIBEVENT_PTIMEUTILS_H
