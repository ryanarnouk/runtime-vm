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
    LOAD_CONST, // load constant (onto stack)
    STORE_VAR,  // store top of stack into variable
    ADD,        // add top two values on the stack
    SUB,        // subtract top two values on the stack
    JE,         // jump if equal to zero
    PRINT,       // print top of the stack
    METHOD_BEGIN, // begin method definition
    METHOD_END,   // end method definition
    NEW,         // create a new object
    DUP,         // duplicate top of stack
    INVOKE_SPECIAL, // invoke a special method (e.g. constructor)
    INVOKE_VIRTUAL, // invoke a virtual method
    INVOKE_STATIC,  // invoke a static method
    LOAD_VAR,       // load a variable onto the stack
    SETFIELD,       // set the field of an object
    GETFIELD,       // get the field of an object
    RETURN          // return from the method
} Instruction;

typedef struct {
    Instruction instruction;
    int operand;
} Bytecode;

void execute_bytecode(VirtualMachine* vm, Bytecode* bytecode, int length);

#endif
