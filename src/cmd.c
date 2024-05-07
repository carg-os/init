#include <cmd.h>

#include <proc.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

typedef struct {
    const char *name;
    int (*func)(int argc, char *argv[]);
    bool builtin;
} cmd_t;

int cmd_clear(int argc, char *argv[]);
int cmd_exit(int argc, char *argv[]);
int cmd_getpid(int argc, char *argv[]);
int cmd_help(int argc, char *argv[]);
int cmd_motd(int argc, char *argv[]);
int cmd_reboot(int argc, char *argv[]);
int cmd_shutdown(int argc, char *argv[]);

static cmd_t CMDS[] = {
    {"clear", cmd_clear, false},       {"exit", cmd_exit, true},
    {"getpid", cmd_getpid, true},      {"help", cmd_help, false},
    {"motd", cmd_motd, false},         {"reboot", cmd_reboot, false},
    {"shutdown", cmd_shutdown, false},
};
static const size_t NR_CMDS = sizeof(CMDS) / sizeof(CMDS[0]);

int cmd_exec(lua_State *l) {
    const cmd_t *cmd = lua_touserdata(l, lua_upvalueindex(1));

    int argc = 0;
    char *argv[] = {nullptr};

    int status;
    if (cmd->builtin) {
        status = cmd->func(argc, argv);
    } else {
        pid_t pid = proc(cmd->func, argv);
        while (wait(&status) != pid)
            ;
    }

    if (status) {
        lua_pushinteger(l, status);
        return 1;
    }

    return 0;
}

void register_cmds(lua_State *l) {
    for (size_t i = 0; i < NR_CMDS; i++) {
        lua_pushlightuserdata(l, &CMDS[i]);
        lua_pushcclosure(l, cmd_exec, 1);
        lua_setglobal(l, CMDS[i].name);
    }
}
