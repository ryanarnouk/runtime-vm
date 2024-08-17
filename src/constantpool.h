// DEPRECATED - will remove soon

// #ifndef CONSTANTPOOL_H
// #define CONSTANTPOOL_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "arc.h"
// #include "bytecode.h"

// #define TAG_STRING 0x01
// #define TAG_CLASS 0x07
// #define TAG_FIELD 0x09
// #define TAG_OBJECT 0x03

// #define MAX_CP_ENTRIES 10
// #define MAX_CLASS_ENTRIES 10

// // This constant pool cannot store methods
// // or classes for now.
// // this is because the string is directly coded into
// // the bytecode for the methods (based on this current implementation)
// // and each class is stored in a separate file with a specific file name
// // that represents the name

// typedef struct {
//     unsigned char tag;
//     union {
//         char *str;
//         struct {
//             int class_index;
//             int name_index;
//             int type_index;
//         } field;
//         int class_index;
//     } info;
// } ConstantPoolEntry;

// typedef struct {
//     ConstantPoolEntry *entries;
//     int size;
//     int capacity;
// } ConstantPool;

// typedef struct {
//     int field_name_index;
//     int field_type;
//     void *value;
// } Field;

// typedef struct {
//     int class_index;
//     Field *fields;
//     int field_count;
//     ArcNode* arc;
// } Object;

// typedef struct {
//     int field_name_index;
//     int field_type_index;
// } FieldInfo;

// typedef struct {
//     FieldInfo *fields;
//     int field_count;
// } ClassInfo;

// typedef struct {
//     ClassInfo *classes;
//     int size;
//     int capacity;
// } ClassTable;

// ConstantPool* create_constant_pool();
// void adjust_pool_capacity_if_needed(ConstantPool *pool);
// void clean_constant_pool(ConstantPool *pool);
// int add_string(ConstantPool *pool, const char *value);
// int add_int(ConstantPool *pool, int value);
// int add_object(ConstantPool *pool, const char *class_name);
// int add_field(ConstantPool *pool, int class_index, const char *field_name, const char *field_type);
// void print_constant_pool(ConstantPool *pool);

// ClassTable* create_class_table();
// void add_class_fields(ClassTable *table, int class_index, FieldInfo *fields, int field_count);
// Object* allocate_object(ConstantPool *pool, ClassTable *table, ArcNode* list, int class_index);
// void retain_object(Object *object);
// void release_object(ArcNode* list, Object *object);

// #endif
