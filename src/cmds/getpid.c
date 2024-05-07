#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cmd_getpid(int argc, char *argv[]) {
    if (argc > 1) {
        fprintf(stderr, "Usage: getpid\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", getpid());
    return EXIT_SUCCESS;
}
