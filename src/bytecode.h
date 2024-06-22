#ifndef BYTECODE_H
#define BYTECODE_H

// Max sizes for the stack and variable storage
#include "stack_vm.h"
#define MAX_STACK_SIZE 100
#define MAX_VARS 10

typedef enum {
    LOAD_CONST, // load constant (onto stack)
    STORE_VAR,  // store top of stack into variable
    ADD,        // add top two values on the stack
    SUB,        // subtract top two values on the stack
    JE,         // jump if equal to zero
    PRINT       // print top of the stack
} Instruction;

typedef struct {
    Instruction instruction;
    int operand;
} Bytecode;

void execute_bytecode(VirtualMachine* vm, Bytecode* bytecode, int length);

#endif
