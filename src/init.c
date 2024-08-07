#include <config.h>
#include <errno.h>
#include <proc.h>
#include <reboot.h>
#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void main(void) {
    printf("Booting up CargOS v%d.%d.%d...\n", VERSION_MAJOR, VERSION_MINOR,
           VERSION_PATCH);

    const char *argv[] = {"shell", nullptr};
    proc(shell, argv);

    while (true) {
        if (wait(nullptr) < 0 && errno == ECHILD) {
            fprintf(stderr, "No process is available; init terminated\n");
            reboot(REBOOT_TYPE_HANG);
        }
    }
}
