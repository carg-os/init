#include <shell.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_motd(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: motd\n");
        _Exit(EXIT_FAILURE);
    }
    print_motd();
    _Exit(EXIT_SUCCESS);
}
