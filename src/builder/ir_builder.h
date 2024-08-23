#ifndef IR_BUILDER_H
#define IR_BUILDER_H

#include "../bytecode.h"
#include "../class/class.h"

// Draft structure, will be split up into deprecated constant pool file

static ClassFile *emit_file;

void import_std();

void print_constant_pool();
void resize_constant_pool();
int add_constant_identifier(char *identifier);
int get_constant_identifier(char *identifier);

void add_code(CodeAttribute* code_block, IROpcode opcode, uint16_t operand);
void save_class_file(char* path, char* name);
void construct_class_file(IRNode *node, CodeAttribute* code_block);
void free_node(IRNode *node);

#endif
