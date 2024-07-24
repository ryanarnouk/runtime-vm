#ifndef CLASS_H
#define CLASS_H

#include <cinttypes>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../data_access/flags.h"
#include "../bytecode.h"

// Constant pool entry tags
#define CONSTANT_CLASS 7
#define CONSTANT_FIELD_REF 9
#define CONSTANT_METHOD_REF 10
#define CONSTANT_STRING 11
#define CONSTANT_INT 8
#define CONTSANT_FLOAT 4
#define CONSTANT_LONG 6
#define CONSTANT_NAME_AND_TYPE 12
#define CONSTANT_EXCEPTION 13
#define CONSTANT_UTF8 1

// Structure to represent the exception table entry
typedef struct {
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
} ExceptionTableEntry;

// // Structure to represent the code attribute
typedef struct {
    uint16_t attribute_name_index;
    uint16_t attribute_length;
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t code_length;
    Bytecode *code;
    uint16_t exception_table_length;
    ExceptionTableEntry* exception_table;
} CodeAttribute;

typedef struct {
    uint32_t bytes;
} Integer;

typedef struct {
    uint32_t high_bytes;
    uint32_t low_bytes;
} Long;

typedef struct {
    uint32_t high_bytes;
    uint32_t low_bytes;
} Double;

typedef struct {
    uint16_t length; // 2 bytes length
    char *bytes; // length bytes (variable length array for UTF-8 String)
} Utf8;

typedef struct {
    Utf8* name;
} Class;

typedef struct {
    Utf8* name;
    Utf8* type;
} NameAndType;

typedef struct {
    Utf8* class_name;
    NameAndType* name_and_type;
} MethodRef;

typedef struct {
    Utf8* class_name;
    NameAndType* name_and_type;
} FieldRef;

typedef struct {
    Utf8* class_name;
    NameAndType* name_and_type;
} InterfaceRef;

// Actual method structure, with code and the constant index for the name
// Code is stored directly in this array. Hashmap lookup can be done if since there will probably
// be too much overhead to store the code directly in the constant pool (where the key may the index number rather than a string)
typedef struct {
    uint16_t name_index; // Index where name is the constant pool
    CodeAttribute* code;
} Method;

// Structure for ConstantPoolEntry
typedef struct {
    uint8_t tag;
    union {
        Class* class_info;
        FieldRef* field_ref_info;
        MethodRef* method_ref_info;
        InterfaceRef* interface_ref_info;
        Utf8* utf8_info;
        Integer* integer_info;
        Long* long_info;
        Double* double_info;
        NameAndType* name_and_type_info;
    } info;
} ConstantPoolEntry;

typedef struct {
    uint16_t minor_version; // 2 bytes minor version
    uint16_t major_version; // 2 bytes major version

    Class *class_name; // class name, defined outside of constant pool for easier record keeping/debugging

    Flags* flags; // 2 bytes access flags

    uint16_t constant_pool_count; // 2 bytes constant pool count
    ConstantPoolEntry *constant_pool_entries; // constant pool

    uint16_t this_class; // 2 bytes reference to "this" class in the constant pool
    uint16_t super_class; // 2 bytes reference to the "super" class in the constant pool

    uint16_t method_count;
    Method *methods;

    // TODO: implement fields and interfaces
} ClassFile;

#endif
