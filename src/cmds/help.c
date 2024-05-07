#include <stdio.h>
#include <stdlib.h>

int cmd_help(int argc, char *argv[]) {
    printf("clear    clear the screen\n");
    printf("exit     quit with the specified status (optional)\n");
    printf("getpid   return the current PID\n");
    printf("help     summon this list\n");
    printf("motd     print the message of the day\n");
    printf("reboot   reboot the whole system\n");
    printf("shutdown shutdown the system\n");
    _Exit(EXIT_SUCCESS);
}
