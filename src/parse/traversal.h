#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "common.h"

// Traverse through the generated nodes created through the parser
// this will also emit the Intermediate Representation (IR) for the bytecode
// interpreter

void emitIL(const char *instruction);
void traverseNode(Node* node);
void freeNode(Node *node);

#endif
