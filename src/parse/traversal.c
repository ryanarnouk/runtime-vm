#include "traversal.h"
#include <stdio.h>
#include <stdlib.h>

void emitIL(const char *instruction) {
    // TODO - implement IL write to bytecode output file
    printf("%s\n", instruction);
}

void traverseNode(Node* node) {
    if (node == NULL) {
        return;
    }

    if (node->type == CLASS_NODE) {
        emitIL("class");
        printf("class %s {\n", node->data.class.name);
        emitIL(node->data.class.name);
        traverseNode(node->data.class.body);
        emitIL("endclass");
        printf("}\n");
    } else if (node->type == IDENTIFIER_NODE) {
        emitIL("identifier");
        emitIL(node->data.identifier);
        printf("identifier %s;\n", node->data.identifier);
    }

    traverseNode(node->next);
}

void freeNode(Node *node) {
    if (node == NULL) {
        return;
    }

    Node *current = node;
    while (current) {
        Node *next = current->next;
        if (current->type == CLASS_NODE) {
            free(current->data.class.name);
            freeNode(current->data.class.body);
        } else if (current->type == IDENTIFIER_NODE) {
            free(current->data.identifier);
        }
        free(current);
        current = next;
    }
}
