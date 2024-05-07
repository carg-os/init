#include <shell.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_shell(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: shell\n");
        _Exit(EXIT_FAILURE);
    }
    shell();
}
