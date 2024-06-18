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

void vm_init() {
    vm.sp = -1;
    memset(vm.vars, 0, sizeof(vm.vars));
}

void vm_push(int value) {
    vm.stack[++vm.sp] = value;
}

int vm_pop() {
    return vm.stack[vm.sp--];
}

void stack_print() {
    printf("Printing content of the stack: \n");
    for (unsigned long i = 0; i < sizeof(vm.stack) / sizeof(int); i++) {
        printf("%d ", vm.stack[i]);
    }
    printf("The stack pointer is: %d", vm.sp);
    printf("\n");
}
