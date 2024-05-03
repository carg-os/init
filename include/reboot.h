#pragma once

#include <errno.h>
#include <stddef.h>

#define REBOOT_REBOOT 0
#define REBOOT_SHUTDOWN 1

static inline int reboot(int type) {
    register size_t a0 asm("a0") = type;
    register size_t a7 asm("a7") = 8;
    asm volatile("ecall" : "+r"(a0) : "r"(a7));
    if ((int) a0) {
        errno = -((int) a0);
        return -1;
    }
    return 0;
}
