#include <config.h>
#include <errno.h>
#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/proc.h>
#include <sys/wait.h>

void init(void) {
    printf("Booting up CargOS v%d.%d.%d...\n", VERSION_MAJOR, VERSION_MINOR,
           VERSION_PATCH);

    char *argv[] = {"shell", nullptr};
    proc(cmd_shell, argv);

    while (true) {
        if (wait(nullptr) < 0 && errno == -ECHILD) {
            printf("No process is available; init terminated\n");
            exit(EXIT_SUCCESS);
        }
    }
}
