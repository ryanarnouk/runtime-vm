// TODO: This file will be split up into a separate constant pool file
// It is currently not functional, but a draft into the direction of thr project
#include "ir_builder.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../class/builder/builder.h"

void write_string(FILE* file, const char* str, uint16_t length) {
    // Matches the UTF-8 structure from class.h
    fwrite(&length, sizeof(uint16_t), 1, file);
    fwrite(str, sizeof(char), length, file);
}

void resize_constant_pool() {
    if (emit_file->constant_pool_capacity == emit_file->constant_pool_count) {
        emit_file->constant_pool_capacity *= 2;
        emit_file->constant_pool_entries = realloc(emit_file->constant_pool_entries, sizeof(ConstantPoolEntry) * emit_file
            ->constant_pool_capacity);
        if (emit_file->constant_pool_entries == NULL) {
            perror("Failed to resize constant pool");
            exit(1);
        }
    }
}

void print_constant_pool() {
    for (uint16_t i = 0; i < emit_file->constant_pool_count; i++) {
        printf("Constant pool tag: %d \n", emit_file->constant_pool_entries[i].tag);
        printf("Constant pool entry %d with value %s \n", i, emit_file->constant_pool_entries[i].info.utf8_info->bytes);
        printf("Constant pool length %d \n", emit_file->constant_pool_entries[i].info.utf8_info->length);;
    }
}

int add_method_identifier(char *identifier) {
    // add a method name to the constant pool
    for (size_t i = 0; i < emit_file->constant_pool_count; i++) {
        if (emit_file->constant_pool_entries[i].tag == CONSTANT_METHOD_REF) {
            if (strcmp(emit_file->constant_pool_entries[i].info.method_ref_info->class_name.bytes, identifier) == 0) {
                return i;
            }
        }
    }

    resize_constant_pool();

    ConstantPoolEntry entry;
    entry.tag = CONSTANT_METHOD_REF;
    entry.info.method_ref_info = malloc(sizeof(MethodRef));
    Utf8 name;
    name.bytes = identifier;
    name.length = strlen(identifier);
    entry.info.method_ref_info->class_name = name;
    emit_file->constant_pool_entries[emit_file->constant_pool_count] = entry;
    return emit_file->constant_pool_count++;
}

// Import tthe standard library methods (which is just standard out for now)
void import_std() {
    // Move this to be imported from the user
    // rather than the standard library automatically being imported
    add_method_identifier("print");

    CodeAttribute *code = malloc(sizeof(CodeAttribute));
    code->attribute_name_index = 1;
    code->attribute_name_index = 1;
    code->max_stack = 1;
    code->max_locals = 1;

    // only supports printing hello world for now
    int string_index = add_constant_identifier("Hello, World!");

    // logic for print is to use STDOUT opcode with the identifier provided (arg)
    add_code(code, IR_STDOUT, string_index);

    // add the method to the method table
    emit_file->method_table->methods_code[emit_file->method_table->method_count] = *code;
    emit_file->method_table->method_count++;
}

int add_constant_identifier(char *identifier) {
    for (size_t i = 0; i < emit_file->constant_pool_count; i++) {
        if (emit_file->constant_pool_entries[i].tag == CONSTANT_UTF8) {
            if (strcmp(emit_file->constant_pool_entries[i].info.utf8_info->bytes, identifier) == 0) {
                return i;
            }
        }
    }

    // If the capacity of the constant pool has been reached, resize it with realloc (double capacity)
    resize_constant_pool();

    ConstantPoolEntry entry;
    entry.tag = CONSTANT_UTF8;
    entry.info.utf8_info = malloc(sizeof(Utf8));
    entry.info.utf8_info->length = strlen(identifier);
    entry.info.utf8_info->bytes = identifier;
    emit_file->constant_pool_entries[emit_file->constant_pool_count] = entry;
    return emit_file->constant_pool_count++;
}

void save_class_file(char* path, char* name) {
    // Concat logic
    char *ptr = path;
    while (*ptr) {
        ptr++;
    }

    *ptr = '/';
    ptr++;

    while (*name) {
        *ptr = *name;
        ptr++;
        name++;
    }

    char* extension = ".rvmc";
    while (*extension) {
        *ptr = *extension;
        ptr++;
        extension++;
    }

    printf("Saved compiled RVMC file: %s \n", path);

    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fwrite(&emit_file->minor_version, sizeof(uint16_t), 1, file);
    fwrite(&emit_file->major_version, sizeof(uint16_t), 1, file);

    write_string(file, emit_file->class_name->bytes, emit_file->class_name->length);

    // Write class_name (UTF-8 string)
    fwrite(&emit_file->flags->access_flags, sizeof(uint16_t), 1, file);

    fwrite(&emit_file->constant_pool_count, sizeof(uint16_t), 1, file);
    fwrite(&emit_file->constant_pool_capacity, sizeof(uint16_t), 1, file);

    // Write constant pool entries
    for (int i = 0; i < emit_file->constant_pool_count; i++) {
        // Write the tag first so that we know what structure to save into
        fwrite(&emit_file->constant_pool_entries[i].tag, sizeof(uint8_t), 1, file);

        switch (emit_file->constant_pool_entries[i].tag) {
            // TODO: extract each case out into a separate function
            case CONSTANT_METHOD_REF:
                write_string(file,
                    emit_file->constant_pool_entries[i].info.method_ref_info->class_name.bytes,
                    emit_file->constant_pool_entries[i].info.method_ref_info->class_name.length);
                break;
            case CONSTANT_UTF8:
                write_string(file,
                    emit_file->constant_pool_entries[i].info.utf8_info->bytes,
                    emit_file->constant_pool_entries[i].info.utf8_info->length);
                break;
        }
    }

    // Write constructor
    fwrite(&emit_file->constructor->attribute_name_index, sizeof(uint16_t), 1, file);
    fwrite(&emit_file->constructor->attribute_length, sizeof(uint16_t), 1, file);
    fwrite(&emit_file->constructor->max_stack, sizeof(uint16_t), 1, file);
    fwrite(&emit_file->constructor->max_locals, sizeof(uint16_t), 1, file);
    //fwrite(&emit_file->constructor->code_length, sizeof(uint32_t), 1, file);

    // for (uint32_t i = 0; i < emit_file->constructor->code_length; i++) {
    //     fwrite(&emit_file->constructor->code[i], sizeof(uint8_t), 1, file);
    // }

    // Iterate through the linked list and add each instruction to the file
    Bytecode *current = emit_file->constructor->code;
    while (current != NULL) {
        fwrite(&current->instruction, sizeof(uint8_t), 1, file);
        fwrite(&current->operand, sizeof(uint16_t), 1, file);
        current = current->next;
    }

    fwrite(&emit_file->this_class, sizeof(uint16_t), 1, file);
    fwrite(&emit_file->super_class, sizeof(uint16_t), 1, file);

    for (size_t i = 0; i < emit_file->method_table->method_count; i++) {
        fwrite(&emit_file->method_table->methods_code[i].attribute_name_index, sizeof(uint16_t), 1, file);
        fwrite(&emit_file->method_table->methods_code[i].attribute_length, sizeof(uint16_t), 1, file);
        fwrite(&emit_file->method_table->methods_code[i].max_stack, sizeof(uint16_t), 1, file);
        fwrite(&emit_file->method_table->methods_code[i].max_locals, sizeof(uint16_t), 1, file);
        // fwrite(&emit_file->method_table->methods_code[i].code_length, sizeof(uint32_t), 1, file);

        // for (uint32_t j = 0; j < emit_file->method_table->methods_code[i].code_length; j++) {
        //     fwrite(&emit_file->method_table->methods_code[i].code[j].instruction, sizeof(uint8_t), 1, file);
        //     fwrite(&emit_file->method_table->methods_code[i].code[j].operand, sizeof(uint16_t), 1, file);
        // }

        Bytecode* curr = emit_file->method_table->methods_code[i].code;
        while (curr != NULL) {
            fwrite(&curr->instruction, sizeof(uint8_t), 1, file);
            fwrite(&curr->operand, sizeof(uint16_t), 1, file);
            curr = curr->next;
        }
    }

    fclose(file);
}

void add_code(CodeAttribute* code_block, IROpcode opcode, uint16_t operand) {
    // Because the code is a variable length that does
    // not need constant access time, it is implemented as a
    // linked list where you can add to the end "next" in succession
    //
    // This is unlike the constant pool which needs a set size and
    // resize approach with realloc to have a constant access time for
    // any location in the pool
    if (code_block->code == NULL) {
        code_block->code = malloc(sizeof(Bytecode));
        code_block->code->instruction = opcode;
        code_block->code->operand = operand;
        code_block->code->next = NULL;
        // code_block->code_length = 1;
    } else {
        Bytecode *current = code_block->code;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = malloc(sizeof(Bytecode));
        current->next->instruction = opcode;
        current->next->operand = operand;
        current->next->next = NULL;
        //code_block->code_length++;
    }
}

int get_constant_identifier(char *identifier) {
    for (size_t i = 0; i < emit_file->constant_pool_count; i++) {
        if (emit_file->constant_pool_entries[i].tag == CONSTANT_UTF8) {
            if (strcmp(emit_file->constant_pool_entries[i].info.utf8_info->bytes, identifier) == 0) {
                return i;
            }
        } else if (emit_file->constant_pool_entries[i].tag == CONSTANT_METHOD_REF) {
            if (strcmp(emit_file->constant_pool_entries[i].info.method_ref_info->class_name.bytes, identifier) == 0) {
                return i;
            }
        }
    }
    return -1;
}

void verbose_print(const char* format, ...) {
    #if VERBOSE_MODE == 1
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    #endif
}

// Add arg to reflect the code attribute to add the generated code to
// will often be null (ex. for identfiers that are only going to be added to
// the constant pool and not generate any specific IR)
void construct_class_file(IRNode *node, CodeAttribute* code_block) {
    if (node == NULL) {
        if (code_block != NULL) {
            // only the constructor is currently supported as a code block
            // Reached the end - emit the code block
            emit_file->constructor = code_block;
            import_std(); // import the standard library
        }
        return;
    }

    switch (node->type) {
        case NODE_IDENTIFIER:
            // increment number of elements in CP and add string constant
            verbose_print("Identifier: %s \n", node->data.identifier);
            if (!node->data.identifier || strlen(node->data.identifier) == 0) {
                return;
            }
            add_constant_identifier(node->data.identifier);
            break;
        case NODE_INTEGER:
            verbose_print("Integer: %d \n", node->data.intval);
            // entry->info.integer_info = malloc(sizeof(Integer));
            // entry->info.integer_info->bytes = node->data.intval;
            break;
        case NODE_CLASS:
            verbose_print("Class: %s \n", node->data.class_declaration.name);
            emit_file = create_class_file(node->data.class_declaration.name);
            construct_class_file(node->data.class_declaration.class_members, code_block);
            break;
        case NODE_CONSTRUCTOR:
            verbose_print("Constructor \n");
            CodeAttribute* constructor = (CodeAttribute *) malloc(sizeof(CodeAttribute));
            // constructor doesn't have an explicit name. Setting the index to 1
            constructor->attribute_name_index = 0;
            constructor->attribute_length = 0; // TODO implement later
            constructor->max_stack = 1; // TODO implement later
            constructor->max_locals = 1; // TODO implement later

            construct_class_file(node->data.constructor_declaration.params, constructor);
            construct_class_file(node->data.constructor_declaration.code_body, constructor);
            break;
        case NODE_FUNCTION_CALL:
            verbose_print("Function call (only print supported right now) \n");
            // for now, only constructor code is supported (and added directly there)
            // and for now, only "print" function call is supported
            int cp_index = get_constant_identifier("print");
            if (cp_index != -1) {
                add_code(code_block, IR_METHOD, cp_index);
            } else {
                perror("Function does not exist");
            }

            construct_class_file(node->data.method_call_declaration.args, code_block);
            break;
        case NODE_ASSIGN:
            verbose_print("Assign %d to %s \n",
                node->data.assignment.right->data.intval,
                node->data.assignment.left->data.identifier);
            construct_class_file(node->data.assignment.left, code_block);
            construct_class_file(node->data.assignment.right, code_block);
            break;
        case NODE_VAR_DECL:
            construct_class_file(node->data.variable_declaration.name, code_block);
            break;
        default:
            // fprintf(stderr, "Opcode does not exist");
            break;
    }

    construct_class_file(node->next, code_block);
}

void free_node(IRNode *node) {
    if (node == NULL) {
        return;
    }

    IRNode *current = malloc(sizeof(IRNode));
    current = node;

    while (current) {
        IRNode *next = current->next;

        switch (node->type) {
            case NODE_IDENTIFIER:
                free(node->data.identifier);
                break;
            case NODE_INTEGER:
                // Nothing in heap to free
                break;
            case NODE_CLASS:
                free(node->data.class_declaration.name);
                free_node(node->data.class_declaration.class_members);
                break;
            case NODE_CONSTRUCTOR:
                free_node(node->data.constructor_declaration.params);
                free_node(node->data.constructor_declaration.code_body);
                break;
            case NODE_FUNCTION_CALL:
                free(node->data.method_call_declaration.name);
                free_node(node->data.method_call_declaration.args);
                break;
            case NODE_ASSIGN:
                free_node(node->data.assignment.left);
                free_node(node->data.assignment.right);
                break;
            case NODE_VAR_DECL:
                free_node(node->data.variable_declaration.name);
                break;
            default:
                break;
        }

        free(current);
        current = next;
    }
}


// TODO: These will be moved to a separate tree-structure file
IRNode *create_identifier_node(char *name) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_IDENTIFIER;
    node->data.identifier = name;
    return node;
}

IRNode *create_integer_node(int value) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_INTEGER;
    node->data.intval = value;
    return node;
}

IRNode *create_class_node(char *name, IRNode *class_members) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_CLASS;
    node->data.class_declaration.name = name;
    node->data.class_declaration.class_members = class_members;
    return node;
}

IRNode *create_constructor_node(IRNode *params, IRNode *code_body) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_CONSTRUCTOR;
    node->data.constructor_declaration.params = params;
    node->data.constructor_declaration.code_body = code_body;
    return node;
}

IRNode *create_method_call_node(char* name, IRNode* args) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_FUNCTION_CALL;
    node->data.method_call_declaration.name = name;
    node->data.method_call_declaration.args = args;
    return node;
}

IRNode *create_assignment_node(IRNode *left, IRNode *right) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_ASSIGN;
    node->data.assignment.left = left;
    node->data.assignment.right = right;
    return node;
}

IRNode *create_var_decl_node(IRNode *name) {
    IRNode *node = malloc(sizeof(IRNode));
    node->type = NODE_VAR_DECL;
    node->data.variable_declaration.name = name;
    return node;
}

IRNode *append_node(IRNode *list, IRNode *node) {
    if (!list) {
        return node;
    }

    IRNode *current = list;
    while (current->next) {
        current = current->next;
    }
    current->next = node;

    return list;
}
