#include <config.h>
#include <errno.h>
#include <proc.h>
#include <reboot.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void start();

void init(void) {
    printf("\e[1;1H\e[2J");
    printf("Booting up CargOS v%d.%d.%d...\n", VERSION_MAJOR, VERSION_MINOR,
           VERSION_PATCH);

    char *argv[] = {"shell", nullptr};
    proc(start, argv);

    while (true) {
        if (wait(nullptr) < 0 && errno == ECHILD) {
            fprintf(stderr, "No process is available; init terminated\n");
            reboot(REBOOT_TYPE_SHUTDOWN);
        }
    }
}
