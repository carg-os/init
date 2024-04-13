#include <cmd.h>

#include <exit_status.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/proc.h>
#include <sys/wait.h>

int cmd_help(int argc, char *argv[]);
int cmd_clear(int argc, char *argv[]);
int cmd_echo(int argc, char *argv[]);
int cmd_exit(int argc, char *argv[]);
int cmd_getpid(int argc, char *argv[]);
int cmd_help(int argc, char *argv[]);
int cmd_shell(int argc, char *argv[]);
int cmd_sleep(int argc, char *argv[]);

cmd_t CMDS[] = {
    {"?", cmd_help, false},       {"clear", cmd_clear, false},
    {"echo", cmd_echo, false},    {"exit", cmd_exit, true},
    {"getpid", cmd_getpid, true}, {"help", cmd_help, false},
    {"shell", cmd_shell, false},  {"sleep", cmd_sleep, false},
};
static size_t NR_CMDS = sizeof(CMDS) / sizeof(CMDS[0]);

int cmd_exec(int argc, char *argv[], bool async) {
    if (argc == 0)
        return EXIT_SUCCESS;

    int status = EXIT_STATUS_UNKNOWN_CMD;
    size_t i;
    for (i = 0; i < NR_CMDS; i++) {
        if (strcmp(argv[0], CMDS[i].name) == 0) {
            status = EXIT_SUCCESS;
            if (CMDS[i].builtin) {
                status = CMDS[i].func(argc, argv);
            } else {
                pid_t pid = proc(CMDS[i].func, argv);
                if (pid < 0) {
                    status = EXIT_STATUS_GENERAL_ERR;
                    break;
                }
                while (!async && wait(&status) != pid)
                    ;
            }
            break;
        }
    }

    if (i == NR_CMDS)
        printf("Unknown command: %s\n", argv[0]);

    return status;
}
