#ifndef COMMON_H
#define COMMON_H

typedef struct Node {
    enum { CLASS_NODE, IDENTIFIER_NODE, INTEGER_NODE } type;
    union {
        char *identifier;
        int integer;
        struct {
            char *name;
            struct Node *body;
        } class;
    } data;
    struct Node *next;
} Node;

extern Node *root;

#endif
