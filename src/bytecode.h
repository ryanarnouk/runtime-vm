#ifndef BYTECODE_H
#define BYTECODE_H

// Max sizes for the stack and variable storage
#include "stack_vm.h"
#define MAX_STACK_SIZE 100
#define MAX_VARS 10

// - `METHOD_BEGIN <method_name>`: Begins the method definition
// - `METHOD_END`: Ends the method definition
// - `NEW <class_name>`: Creates a new object of the class
// - `DUP`: Duplicates the top of the stack
// - `STORE_VAR <constant>`: Stores the top of the stack into a variable
// - `INVOKE_SPECIAL <class_name> <method_name>`: Invokes a constructor method (or any other "special" method)
// - `INVOKE_VIRTUAL <class_name> <method_name>`: Invokes a virtual method
// - `INVOKE_STATIC <class_name> <method_name>`: Invokes a static method
// - `LOAD_CONST <constant>`: Loads a constant onto the stack
// - `LOAD_VAR`: Loads a variable onto the stack
// - `SETFIELD fieldName`: Sets the field of an object
// - `GETFIELD fieldName`: Gets the field of an object
// - `RETURN`: Returns from the method

typedef enum {
    LOAD_CONST, // 0: load constant (onto stack)
    STORE_VAR,  // 1: store top of stack into variable
    ADD,        // 2: add top two values on the stack
    SUB,        // 3: subtract top two values on the stack
    JE,         // 4: jump if equal to zero
    PRINT,       // 5: print top of the stack
    METHOD_BEGIN, // 6: begin method definition
    METHOD_END,   // 7: end method definition
    NEW,         // 8: create a new object
    DUP,         // 9: duplicate top of stack
    INVOKE_SPECIAL, // 10: invoke a special method (e.g. constructor)
    INVOKE_VIRTUAL, // 11: invoke a virtual method
    INVOKE_STATIC,  // 12: invoke a static method
    LOAD_VAR,       // 13: load a variable onto the stack
    SETFIELD,       // 14: set the field of an object
    GETFIELD,       // 15: get the field of an object
    RETURN          // 16: return from the method
} Instruction;

#if FEATURE_FLAG_NEW_PARSER == 0

typedef struct {
    Instruction instruction;
    int operand;
} Bytecode;

#endif

#if FEATURE_FLAG_NEW_PARSER == 1

// a chunk of consecutive bytecode instructions for a method
// based on new and updated instruction set
// TODO

#endif

#endif
