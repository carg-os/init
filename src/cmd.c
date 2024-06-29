#include <cmd.h>

#include <proc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct {
    const char *name;
    int (*func)(int argc, char *argv[]);
    bool builtin;
} cmd_t;

int cmd_banner(int argc, char *argv[]);
int cmd_clear(int argc, char *argv[]);
int cmd_exit(int argc, char *argv[]);
int cmd_getpid(int argc, char *argv[]);
int cmd_help(int argc, char *argv[]);
int cmd_reboot(int argc, char *argv[]);
int cmd_shell(int argc, char *argv[]);
int cmd_shutdown(int argc, char *argv[]);
int cmd_sleep(int argc, char *argv[]);

static cmd_t CMDS[] = {
    {"banner", cmd_banner, false},     {"clear", cmd_clear, false},
    {"exit", cmd_exit, true},          {"getpid", cmd_getpid, true},
    {"help", cmd_help, false},         {"reboot", cmd_reboot, false},
    {"shutdown", cmd_shutdown, false}, {"shell", cmd_shell, false},
    {"sleep", cmd_sleep, false},
};
static const size_t NR_CMDS = sizeof(CMDS) / sizeof(CMDS[0]);

int cmd_exec(lua_State *l) {
    const cmd_t *cmd = lua_touserdata(l, lua_upvalueindex(1));

    int argc = lua_gettop(l) + 1;
    char **argv = (char **) malloc(sizeof(char *) * (argc + 1));
    argv[0] = strdup(cmd->name);
    for (int i = 1; i < argc; i++) {
        argv[i] = strdup(lua_tostring(l, i));
    }
    argv[argc] = nullptr;

    int status;
    if (cmd->builtin) {
        status = cmd->func(argc, argv);
    } else {
        pid_t pid = proc(cmd->func, argv);
        while (wait(&status) != pid)
            ;
    }

    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);

    if (status)
        printf("\x1B[0;31m%d\x1B[0;0m ", status);

    return 0;
}

void register_cmds(lua_State *lua) {
    for (size_t i = 0; i < NR_CMDS; i++) {
        lua_pushlightuserdata(lua, &CMDS[i]);
        lua_pushcclosure(lua, cmd_exec, 1);
        lua_setglobal(lua, CMDS[i].name);
    }
}
