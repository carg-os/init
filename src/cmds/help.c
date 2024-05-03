#include <stdio.h>
#include <stdlib.h>

int cmd_help(int argc, char *argv[]) {
    printf("?/help   summon this list\n");
    printf("clear    clear the screen\n");
    printf("echo     print the given text\n");
    printf("exit     quit with the specified status (optional)\n");
    printf("getpid   return the current PID\n");
    printf("motd     print the message of the day\n");
    printf("reboot   reboot the whole system\n");
    printf("shell    create another instance of this shell\n");
    printf("sleep    sleep for a certain number of seconds\n");
    printf("shutdown shutdown the system\n");
    exit(EXIT_SUCCESS);
}
