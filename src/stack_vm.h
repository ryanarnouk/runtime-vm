#ifndef STACK_VM_H
#define STACK_VM_H

#define MAX_STACK_SIZE 100
#define MAX_VARS 10
#define MAX_METHODS 10

#include <stddef.h>

typedef struct {
    int stack[MAX_STACK_SIZE];
    int sp; // stack pointer
    int vars[MAX_VARS];
} VirtualMachine;

void* stack_alloc(size_t size);
void stack_free(void* ptr);
VirtualMachine* vm_init();
void vm_push(VirtualMachine* vm, int value);
int vm_pop(VirtualMachine* vm);
void stack_print(VirtualMachine* vm);
void vm_free(VirtualMachine* vm);

#endif
