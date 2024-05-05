#include <config.h>
#include <errno.h>
#include <proc.h>
#include <reboot.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void start();

void init(void) {
    printf("Booting up CargOS v%d.%d.%d...\n", VERSION_MAJOR, VERSION_MINOR,
           VERSION_PATCH);

    char *argv[] = {"shell", nullptr};
    proc(start, argv);

    while (true) {
        if (wait(nullptr) < 0 && errno == ECHILD) {
            printf("No process is available; init terminated\n");
            reboot(REBOOT_SHUTDOWN);
        }
    }
}
