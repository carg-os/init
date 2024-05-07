#include <reboot.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_shutdown(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: shutdown\n");
        _Exit(EXIT_FAILURE);
    }
    _Exit(reboot(REBOOT_TYPE_SHUTDOWN));
}
