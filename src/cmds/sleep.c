#include <sleepns.h>
#include <stdio.h>
#include <stdlib.h>

int cmd_sleep(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: sleep TIME\n");
        _Exit(EXIT_FAILURE);
    }
    float time = atof(argv[1]);
    sleepns(NS_IN_SEC * time);
    _Exit(EXIT_SUCCESS);
}
