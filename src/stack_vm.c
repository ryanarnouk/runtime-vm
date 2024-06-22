#include "stack_vm.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void* stack_alloc(size_t size) {
    return malloc(size);
}

void stack_free(void* ptr) {
    free(ptr);
}

VirtualMachine* vm_init() {
    VirtualMachine* vm = (VirtualMachine *) malloc(sizeof(VirtualMachine));
    vm->sp = -1;
    memset(vm->vars, 0, sizeof(vm->vars));
    return vm;
}

void vm_push(VirtualMachine* vm, int value) {
    vm->stack[++vm->sp] = value;
}

int vm_pop(VirtualMachine* vm) {
    return vm->stack[vm->sp--];
}

void vm_free(VirtualMachine* vm) {
    free(vm);
}

void stack_print(VirtualMachine* vm) {
    printf("Printing content of the stack: \n");
    for (unsigned long i = 0; i < sizeof(vm->stack) / sizeof(int); i++) {
        printf("%d ", vm->stack[i]);
    }
    printf("The stack pointer is: %d", vm->sp);
    printf("\n");
}
