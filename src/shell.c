#include <shell.h>

#include <cmd.h>
#include <config.h>
#include <stdio.h>
#include <tok.h>

int cmd_shell(int argc, char *argv[]) {
    print_motd();

    while (true) {
        printf("$ ");

        char cmd_buf[CMD_BUF_SIZE];
        gets(cmd_buf);

        tok_t tok_buf[TOK_BUF_SIZE];
        size_t nr_toks = tokenize(cmd_buf, tok_buf);

        int argc = 0;
        char *argv[ARG_BUF_SIZE];
        bool async = false;

        bool quit = false;
        for (size_t i = 0; i < nr_toks; i++) {
            switch (tok_buf[i].type) {
            case TOK_TYPE_CMD_OR_ARG:
                argv[argc] = tok_buf[i].start;
                argc++;
                break;
            case TOK_TYPE_ASYNC:
                async = true;
                break;
            case TOK_TYPE_AND:
            case TOK_TYPE_NEWLINE: {
                argv[argc] = nullptr;
                int status = cmd_exec(argc, argv, async);
                if (status) {
                    printf("\x1B[0;31m%d \x1B[0;0m", status);
                    quit = true;
                }
                argc = 0;
                async = false;
                break;
            }
            case TOK_TYPE_OR: {
                argv[argc] = nullptr;
                int status = cmd_exec(argc, argv, async);
                if (!status)
                    quit = true;
                argc = 0;
                async = false;
                break;
            }
            }

            if (quit) {
                break;
            }
        }
    }
}
