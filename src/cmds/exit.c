#include <stdio.h>
#include <stdlib.h>

int cmd_exit(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: exit [STATUS]\n");
        return EXIT_FAILURE;
    }
    int status = 0;
    if (argc == 2) {
        char *end;
        status = strtol(argv[1], &end, 10);
        if (*end != '\0') {
            fprintf(stderr, "exit: numeric argument required\n");
            return EXIT_FAILURE;
        }
    }
    _Exit(status);
}
