#include <reboot.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_reboot(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: reboot\n");
        _Exit(EXIT_FAILURE);
    }
    _Exit(reboot(REBOOT_TYPE_REBOOT));
}
