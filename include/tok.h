#ifndef TOK_H_
#define TOK_H_

#include <stddef.h>

typedef enum {
    TOK_TYPE_CMD_OR_ARG,
    TOK_TYPE_ASYNC,
    TOK_TYPE_AND,
    TOK_TYPE_OR,
    TOK_TYPE_NEWLINE,
} tok_type_t;

typedef struct {
    tok_type_t type;
    char *start;
    size_t size;
} tok_t;

size_t tokenize(char *cmd_buf, tok_t *tok_buf);

#endif // TOK_H_
