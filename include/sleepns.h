#pragma once

#include <errno.h>
#include <time.h>

#define NS_IN_SEC 1000000000

static inline int sleepns(time_t ns) {
    register size_t a0 asm("a0") = ns;
    register size_t a7 asm("a7") = 4;
    asm volatile("ecall" : "+r"(a0) : "r"(a7));
    if ((int) a0 < 0) {
        errno = -((int) a0);
        return -1;
    }
    return a0;
}
