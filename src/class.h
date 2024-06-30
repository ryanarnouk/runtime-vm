#ifndef CLASS_H
#define CLASS_H

#include "bytecode.h"
#include <stdio.h>

typedef struct {
    char* name;
    Bytecode* bytecode;
    int bytecode_length;
} Method;

typedef struct {
    char* class_name;
    Method* methods;
    int method_count;
} Class;

// key-value pair structure for storing class methods
typedef struct NameMethodPair {
    char* name;
    Method* method;
    struct NameMethodPair* next;
} NameMethodPair;

// Hash map structure
typedef struct HashMap {
    size_t size; // Size of the hash table (number of buckets)
    NameMethodPair** buckets; // Array of pointers to head of the linked lists (buckets)
} HashMap;

Class* load_class(const char* filename, HashMap* map);
void clean_class(Class* c);

Method* load_methods(FILE* file, int* method_count, HashMap* map);
void print_methods(Method* methods, int method_count);

// This is a very basic implementation of a hash map for storing class methods
// It uses a simple hash functioning
// Collision resolution is done by chaining (with linked lists). Each bucket with a collsion
// will then need to iterate through the linked list to find the correct key-value pair

// simple hashing function
unsigned long hash_function(const char *str);
HashMap* create_map(size_t size);
void insert(HashMap* map, const char* name, Method* fn);
int search(HashMap* map, const char* name, Method* fn);
void clean_map(HashMap* map);
void print_map(HashMap* map);

#endif
