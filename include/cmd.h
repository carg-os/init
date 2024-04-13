#ifndef CMD_H_
#define CMD_H_

typedef struct {
    const char *name;
    int (*func)(int argc, char *argv[]);
    bool builtin;
} cmd_t;

extern cmd_t cmds[];

int cmd_exec(int argc, char *argv[], bool async);

#endif // CMD_H_
