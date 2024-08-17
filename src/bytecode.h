#ifndef BYTECODE_H
#define BYTECODE_H

// Max sizes for the stack and variable storage
#include "stack_vm.h"
#include "stdint.h"
#include "common_properties.h"
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

#if FEATURE_FLAG_NEW_PARSER == 0

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
    IRRETURN          // 16: return from the method
} Instruction;

typedef struct {
    Instruction instruction;
    int operand;
} Bytecode;

#endif

#if FEATURE_FLAG_NEW_PARSER == 1

// Prefix of each enum begins with IR avoid any
// redeclarations used for the old bytecode instructions
//
// TODO: make this header file simply declare the Opcodes/bytecode
// not every single little detail related to the construction of the tree
// which should solely be handled by the parser
typedef enum {
    IR_LOAD_CONST, // 0
    IR_STORE_VAR, // 1
    IR_ASSIGN, // 2
    IR_INVOKE_SPECIAL, // 3 constructor
    IR_METHOD, // 4 used for "print" method

    // Testing new IR instructions:
    // Standard instructions for the stack machine
    IR_STDOUT // standard out for print method
} IROpcode;

typedef struct Bytecode {
    IROpcode instruction;
    uint16_t operand; // Most likely a reference to the constant pool entry
    struct Bytecode *next;
} Bytecode;

// Prefix of each enum begins with "NODE_" to avoid any
// redeclarations used for constants in the lexer
typedef enum {
    NODE_IDENTIFIER,
    NODE_INTEGER,
    NODE_CLASS,
    NODE_CONSTRUCTOR,
    NODE_FUNCTION_CALL,
    NODE_ASSIGN,
    NODE_VAR_DECL,
} IRNodeType;

typedef struct IRNode {
    IRNodeType type; // type/opcode
    union {
        char *identifier;
        int intval;
        struct {
            char *name;
            struct IRNode *class_members;
            //struct IRNode *methods;
        } class_declaration;
        struct {
            struct IRNode *params;
            struct IRNode *code_body;
        } constructor_declaration;
        struct {
            // will be used for the print statement for now
            char *name;
            struct IRNode *args;
        } method_call_declaration;
        struct {
            struct IRNode *left;
            struct IRNode *right;
        } assignment;
        struct {
            struct IRNode *name;
        } variable_declaration;
    } data;
    struct IRNode *next;
} IRNode;

extern IRNode *root;

IRNode *create_identifier_node(char *name);
IRNode *create_integer_node(int value);
IRNode *create_class_node(char *name, IRNode *class_members);
IRNode *create_constructor_node(IRNode *params, IRNode *code_body);
IRNode *create_method_call_node(char* name, IRNode* args);
IRNode *create_assignment_node(IRNode *left, IRNode *right);
IRNode *create_var_decl_node(IRNode *name);
IRNode *append_node(IRNode *list, IRNode *node);

#endif

#endif
