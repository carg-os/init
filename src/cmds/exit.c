#include <stdio.h>
#include <stdlib.h>

int cmd_exit(int argc, char *argv[]) {
    if (argc != 1 && argc != 2) {
        printf("Usage: exit [STATUS]\n");
        return EXIT_FAILURE;
    }
    int status = argc == 2 ? atoi(argv[1]) : 0;
    exit(status);
}
