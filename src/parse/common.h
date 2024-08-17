#ifndef COMMON_H
#define COMMON_H

typedef enum {
    CLASS_NODE,
    IDENTIFIER_NODE,
    INTEGER_NODE,
    STATEMENT_NODE,
    FUNCTION_NODE,
    EXPRESSION_NODE,
    CONSTRUCTOR_NODE,
} NodeType;

typedef struct Node {
    NodeType type;
    struct Node *left;
    struct Node *right;
    union {
        char *identifier;
        int integer;
        // Class identifier
        struct {
            char *name;
            struct Node *fields;
            struct Node *methods;
        } class_decl;

        // Functions
        struct {
            char *name;
            struct Node *params;
            struct Node *body;
        } function;

        // Statements (return, if, and while)
        struct {
            struct Node *next;
            struct Node *statement;
        } statement;

        // Expressions
        struct {
            char *identify;
            int number;
            struct Node* left;
            struct Node* right;
        } expression;
    } data;
    struct Node *next;
} Node;

extern Node *root;

#endif
