#include <shell.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_banner(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: banner\n");
        _Exit(EXIT_FAILURE);
    }
    print_banner();
    _Exit(EXIT_SUCCESS);
}
