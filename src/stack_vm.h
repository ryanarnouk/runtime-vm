#ifndef STACK_VM_H
#define STACK_VM_H

#define MAX_STACK_SIZE 100
#define MAX_VARS 10

#include <stddef.h>

typedef struct {
    int stack[MAX_STACK_SIZE];
    int sp; // stack pointer
    int vars[MAX_VARS];
} VirtualMachine;

extern VirtualMachine vm;

void* stack_alloc(size_t size);
void stack_free(void* ptr);
void vm_init();
void vm_push(int value);
int vm_pop();
void stack_print();

#endif
