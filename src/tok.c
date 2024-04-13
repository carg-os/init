#include <tok.h>

#include <ctype.h>
#include <string.h>

size_t tokenize(char *cmd_buf, tok_t *tok_buf) {
    while (isspace(*cmd_buf)) {
        ++cmd_buf;
    }

    size_t top = 0;
    while (*cmd_buf) {
        char *start = cmd_buf;
        while (!isspace(*cmd_buf) && *cmd_buf) {
            cmd_buf++;
        }
        size_t size = cmd_buf - start;

        if (strncmp(start, "&", size) == 0) {
            tok_buf[top].type = TOK_TYPE_ASYNC;
        } else if (strncmp(start, "&&", size) == 0) {
            tok_buf[top].type = TOK_TYPE_AND;
        } else if (strncmp(start, "||", size) == 0) {
            tok_buf[top].type = TOK_TYPE_OR;
        } else {
            tok_buf[top].type = TOK_TYPE_CMD_OR_ARG;
        }

        tok_buf[top].start = start;
        tok_buf[top].size = size;
        top++;

        while (isspace(*cmd_buf)) {
            *cmd_buf = '\0';
            cmd_buf++;
        }
    }

    tok_buf[top].type = TOK_TYPE_NEWLINE;
    tok_buf[top].start = cmd_buf;
    tok_buf[top].size = 1;
    top++;

    return top;
}
