#include <stdio.h>
#include <stdlib.h>

int cmd_exit(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: exit [STATUS]\n");
        return EXIT_FAILURE;
    }
    int status = argc == 2 ? atoi(argv[1]) : 0;
    _Exit(status);
}
