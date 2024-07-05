#pragma once

#include <errno.h>
#include <stddef.h>

static inline int proc(void *entry, const char *argv[]) {
    register size_t a0 asm("a0") = (size_t) entry;
    register size_t a1 asm("a1") = (size_t) argv;
    register size_t a7 asm("a7") = 6;
    asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a7));
    if ((int) a0 < 0) {
        errno = -((int) a0);
        return -1;
    }
    return a0;
}
