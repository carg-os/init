#include <stdio.h>
#include <stdlib.h>

int cmd_clear(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: clear\n");
        _Exit(EXIT_FAILURE);
    }
    printf("\e[1;1H\e[2J");
    _Exit(EXIT_SUCCESS);
}
