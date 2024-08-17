#include "traversal.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

// void emitIL(const char *instruction) {
//     // TODO - implement IL write to bytecode output file
//     printf("%s\n", instruction);
// }

// void emitILInt(int int_instr) {
//     printf("%d\n", int_instr);
// }

// void traverseNode(Node* node) {
//     if (node == NULL) {
//         return;
//     }

//     switch (node->type) {
//         case CLASS_NODE:
//             emitIL("class");
//             printf("class %s {\n", node->data.class_decl.name);
//             emitIL(node->data.class_decl.name);
//             traverseNode(node->data.class_decl.methods);
//             traverseNode(node->data.class_decl.fields); // Updated to "members"
//             emitIL("endclass");
//             printf("}\n");
//             break;

//         case FUNCTION_NODE:
//             emitIL("function");
//             emitIL(node->data.function.name);
//             printf("function %s() {\n", node->data.function.name);
//             traverseNode(node->data.function.body);
//             emitIL("endfunction");
//             printf("}\n");
//             break;

//         case IDENTIFIER_NODE:
//             emitIL("identifier");
//             emitIL(node->data.expression.identify);
//             printf("identifier %s;\n", node->data.expression.identify);
//             break;

//         case INTEGER_NODE:
//             emitIL("number");
//             emitILInt(node->data.expression.number);
//             printf("number %d;\n", node->data.expression.number);
//             break;

//         default:
//             printf("Unknown node type\n");
//             break;
//     }

//     traverseNode(node->next);
// }

// void freeNode(Node *node) {
//     if (node == NULL) {
//         return;
//     }

//     Node *current = node;
//     while (current) {
//         Node *next = current->next;

//         switch (current->type) {
//             case CLASS_NODE:
//                 free(current->data.class_decl.name);
//                 freeNode(current->data.class_decl.fields); // Updated to "members"
//                 freeNode(current->data.class_decl.methods);
//                 break;

//             case FUNCTION_NODE:
//                 free(current->data.function.name);
//                 freeNode(current->data.function.body);
//                 break;

//             case IDENTIFIER_NODE:
//                 free(current->data.expression.identify);
//                 break;

//             case INTEGER_NODE:
//                 // No dynamic memory to free for number node
//                 break;

//             default:
//                 printf("Unknown node type\n");
//                 break;
//         }

//         free(current);
//         current = next;
//     }
// }
