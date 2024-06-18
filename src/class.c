#include "class.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Class* load_class(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        fprintf(stderr, "Failed to open class file: %s \n", filename);
        return NULL;
    }

    Class* class = (Class *) malloc(sizeof(Class));
    class->class_name = strdup(filename);
    class->method_count = 1;
    class->methods = (Method *) malloc(sizeof(Method) * class->method_count);

    Method* method = &class->methods[0];
    method->name = strdup("main");
    // TODO: adjust the max number of instructions from 100 (size of the byte code)
    method->bytecode = (Bytecode *) malloc(sizeof(Bytecode) * 100);
    method->bytecode_length = 0;

    int instruction, operand;
    while (fscanf(file, "%d %d", &instruction, &operand) != EOF) {
        // set the enum for the instruction
        method->bytecode[method->bytecode_length].instruction = (Instruction) instruction;
        method->bytecode[method->bytecode_length].operand = operand;
        method->bytecode_length++;
    }
    fclose(file);

    return class;
}

// Instruction parse_instruction(const char *instr) {
//     switch ()
// }

void clean_class(Class *c) {
    free(c->methods[0].name);
    free(c->methods[0].bytecode);
    free(c->methods);
    free(c->class_name);
    free(c);
}
