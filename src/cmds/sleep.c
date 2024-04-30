#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmd_sleep(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: sleep TIME\n");
        exit(EXIT_FAILURE);
    }
    time_t time = atoll(argv[1]);
    sleepns(time * NS_IN_SEC);
    exit(EXIT_SUCCESS);
}
