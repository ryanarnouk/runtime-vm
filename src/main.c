#include <stdio.h>
#include <stdlib.h>
#include "arc.h"
#include "bytecode.h"
#include "stack_vm.h"
#include "engine/interpreter.h"
#include <unistd.h>

// When set to 1, use the new code parser I am working on implementing
// with a constant pool. 0 uses the pre-existing implementation
// that already works as a basic interpreter with a few instructions.
#define FEATURE_FLAG_NEW_PARSER 1

#if FEATURE_FLAG_NEW_PARSER == 1

#include "./class/loader/loader.h"

#endif

#if FEATURE_FLAG_NEW_PARSER == 0

#include "class.h"

#endif

int main(int argc, char *argv[]) {
    int opt;
    char* bytecode_file = NULL;
    char* language_file = NULL;

    if ((opt = getopt(argc, argv, "b:l:")) != -1) {
        switch (opt) {
            case 'b':
                bytecode_file = optarg;
                break;
            case 'l':
                language_file = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-b bytecode_file] [-l language_file]\n", argv[0]);
                return 1;
        }
    }

    if (bytecode_file != NULL && language_file != NULL) {
        fprintf(stderr, "Cannot specify both bytecode and langauge representation files\n");
        return 1;
    }

    if (language_file != NULL) {
        fprintf(stderr, "Language file not yet supported. Parsing/lexing has yet to be implemented for the more abstracted language representation. \n");
        return 1;
    }

    if (bytecode_file == NULL && language_file == NULL) {
        fprintf(stderr, "No language file specified. Please specify a bytecode or language file. \n");
        exit(EXIT_FAILURE);
    }

    #if FEATURE_FLAG_NEW_PARSER == 1
    // Feature flag is set - use the new parser (from preprocessor if-statemnet)
    ClassFile* class = load_class_file(bytecode_file);
    if (!class) {
        fprintf(stderr, "Failed to load class file: %s \n", bytecode_file);
        return 1;
    }
    free(class);
    #endif

    #if FEATURE_FLAG_NEW_PARSER == 0

    // create map to store methods during program execution and bytecode reading
    HashMap* map = create_map(MAX_METHODS);

    // Otherwise, we have a good file the runtime can work with.
    Class* class = load_class(bytecode_file, map);
    if (!class) {
        fprintf(stderr, "Failed to load class file: %s \n", bytecode_file);
        return 1;
    }

    VirtualMachine* vm = vm_init();
    Method* main_method = (Method *) malloc(sizeof(Method));

    if(!search(map, "main", main_method)) {
        fprintf(stderr, "Failed to find main method in class file: %s \n", bytecode_file);
        return 1;
    }

    // main method is found (entry point to the program). Execute it.
    printf("Executing method: %s \n", main_method->name);
    execute_bytecode(vm, main_method->bytecode, main_method->bytecode_length);

    // Example of ARC instead of garbage collection (to be added to the bytecode with OOP)
    ArcNode* list = NULL;
    ArcNode* arc1 = arc_create(&list, 20);
    ArcNode* arc2 = arc_create(&list, 10);

    arc_retain(arc1);
    arc_retain(arc2);
    arc_release(&list, arc1);

    arc_cleanup(&list);
    if (list != NULL) {
        fprintf(stderr, "Could not clean up the heap on program termination \n");
    }

    free(main_method);
    clean_map(map);
    clean_class(class);
    vm_free(vm);
    #endif

    return 0;
}
