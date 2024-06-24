#include "class.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bytecode.h"

// TODO: Maybe change this to return a hash map instead so we can easily reference "main" method
// during execution and then jump to other methods as they are called during the execution
// of the program (and implement returns)
Method* load_methods(FILE* file, int* method_count) {
    int method_instruction;
    char name[256]; // Assuming method names won't exceed 255 characters
    Method* result = (Method *) malloc(sizeof(Method) * 100);
    int number_of_methods = 0;

    while (fscanf(file, "%d %255s", &method_instruction, name) != EOF) {
        if (method_instruction == METHOD_BEGIN) {
            // New method definition
            Method* method = (Method *) malloc(sizeof(Method));
            method->name = strdup(name);
            method->bytecode = (Bytecode *) malloc(sizeof(Bytecode) * 100);
            method->bytecode_length = 0;

            int instruction, operand;
            while (fscanf(file, "%d %d", &instruction, &operand) != EOF) {
                if (instruction == METHOD_END) {
                    // A method ending instruction has occurred
                    break;
                }

                method->bytecode[method->bytecode_length].instruction = (Instruction) instruction;
                method->bytecode[method->bytecode_length].operand = operand;
                method->bytecode_length++;
            }

            // Reallocate the max bytecode size to only the footprint of what was used
            method->bytecode = (Bytecode *) realloc(method->bytecode, sizeof(Bytecode) * method->bytecode_length);

            result[number_of_methods] = *method;
            number_of_methods++;
            free(method); // Free the temporary method struct, since it's copied into result array
        } else {
            // Handle unexpected instruction by skipping to the next line
            fscanf(file, "%*[^\n]");
        }
    }

    result = realloc(result, sizeof(Method) * number_of_methods);
    *method_count = number_of_methods;
    return result;
}

Class* load_class(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        fprintf(stderr, "Failed to open class file: %s \n", filename);
        return NULL;
    }

    Class* class = (Class *) malloc(sizeof(Class));
    class->class_name = strdup(filename);

    int method_count = 0;
    class->methods = load_methods(file, &method_count);
    class->method_count = method_count;

    fclose(file);

    return class;
}

void clean_class(Class *c) {
    for (int i = 0; i < c->method_count; i++) {
        free(c->methods[i].name);
        free(c->methods[i].bytecode);
    }
    free(c->methods);
    free(c->class_name);
    free(c);
}

void print_methods(Method *methods, int method_count) {
    for (int i = 0; i < method_count; i++) {
        Method method = methods[i];
        if (method.name == NULL) {
            break;
        }
        printf("Method: %s\n", method.name);
        for (int j = 0; j < method.bytecode_length; j++) {
            Bytecode bc = method.bytecode[j];
            printf("Instruction: %d Operand: %d\n", bc.instruction, bc.operand);
        }
    }
}
