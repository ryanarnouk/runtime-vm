#ifndef CLASS_H
#define CLASS_H

#include "bytecode.h"
#include <stdio.h>

typedef struct {
    char* name;
    Bytecode* bytecode;
    int bytecode_length;
} Method;

typedef struct {
    char* class_name;
    Method* methods;
    int method_count;
} Class;

Class* load_class(const char* filename);
void clean_class(Class* c);

Method* load_methods(FILE* file, int* method_count);
void print_methods(Method* methods, int method_count);

#endif
