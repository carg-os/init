#pragma once

#include <errno.h>
#include <stddef.h>

typedef enum {
    REBOOT_TYPE_REBOOT = 0,
    REBOOT_TYPE_SHUTDOWN = 1,
    REBOOT_TYPE_HANG = 2,
} reboot_type_t;

static inline int reboot(reboot_type_t type) {
    register size_t a0 asm("a0") = type;
    register size_t a7 asm("a7") = 8;
    asm volatile("ecall" : "+r"(a0) : "r"(a7));
    if ((int) a0 < 0) {
        errno = -((int) a0);
        return -1;
    }
    return a0;
}
