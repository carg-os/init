#include <stdio.h>
#include <stdlib.h>

int cmd_help(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: help\n");
        _Exit(EXIT_FAILURE);
    }
    printf("banner   show the banner of CargOS\n");
    printf("clear    clear the screen\n");
    printf("exit     quit with the specified status (optional)\n");
    printf("getpid   return the current PID\n");
    printf("help     summon this list\n");
    printf("reboot   reboot the whole system\n");
    printf("shell    create another instance of this shell\n");
    printf("shutdown shutdown the system\n");
    printf("sleep    sleep for a certain number of seconds\n");
    _Exit(EXIT_SUCCESS);
}
