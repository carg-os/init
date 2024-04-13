#include <stdio.h>
#include <stdlib.h>

int cmd_help(int argc, char *argv[]) {
    printf("?/help\tsummon this list\n");
    printf("clear\tclear the screen\n");
    printf("echo\tprint the given text\n");
    printf("exit\tquit with the specified status (optional)\n");
    printf("getpid\treturn the current PID\n");
    printf("shell\tcreate another instance of this shell\n");
    printf("sleep\tsleep for a certain number of seconds\n");
    exit(0);
}
