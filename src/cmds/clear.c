#include <stdio.h>
#include <stdlib.h>

int cmd_clear(int argc, char *argv[]) {
    printf("\e[1;1H\e[2J");
    exit(EXIT_SUCCESS);
}
