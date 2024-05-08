#include <sleepns.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_sleep(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: sleep TIME\n");
        _Exit(EXIT_FAILURE);
    }
    char *end;
    float time = strtof(argv[1], &end);
    if (*end != '\0') {
        fprintf(stderr, "sleep: numeric argument required\n");
        _Exit(EXIT_FAILURE);
    }
    sleepns(NS_IN_SEC * time);
    _Exit(EXIT_SUCCESS);
}
