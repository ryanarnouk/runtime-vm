#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arc.h"
#include "builder/ir_builder.h"
#include "bytecode.h"
#include "parse/traversal.h"
#include "stack_vm.h"
#include <string.h>
#include <unistd.h>
#include "common_properties.h"

// When set to 1, use the new code parser I am working on implementing
// with a constant pool. 0 uses the pre-existing implementation
// that already works as a basic interpreter with a few instructions.

#if FEATURE_FLAG_NEW_PARSER == 1

#include "./class/loader/loader.h"
#include "./parse/parser.tab.h"

// Forward declaration from parser.tab.h
int yyparse();
int yylex_destroy (void);
extern FILE *yyin;

#endif

#if FEATURE_FLAG_NEW_PARSER == 0

#include "engine/interpreter.h"
#include "class.h"

#endif

void gen_save_location(char* language_file, char** directory, char **file_name) {
    int length = strlen(language_file);
    int index = length;
    int dot_index = -1;

    char* path_for_rvmc = NULL;
    char* name;
    while (index >=0) {
        index--;
        if (language_file[index] == '/') {
            path_for_rvmc = (char *) malloc(index + 1);
            name = (char*) malloc(length - index);

            strncpy(path_for_rvmc, language_file, index);
            path_for_rvmc[index] = '\0';

            if (dot_index >= 0) {
                strncpy(name, &language_file[index + 1], dot_index - index - 1);
                name[dot_index - index - 1] = '\0';
            } else {
                strcpy(name, &language_file[index + 1]);
            }

            break;
        }

        if (language_file[index] == '.' && dot_index == -1) {
            dot_index = index;
        }

        // No '/' means the entire string is the file name
        if (index < 0) {
            path_for_rvmc = NULL;
            if (dot_index >= 0) {
                name = (char *)malloc(dot_index + 1);
                strncpy(name, language_file, dot_index);
                name[dot_index] = '\0';
            }
        }
    }

    *directory = path_for_rvmc;
    *file_name = name;
}

int main(int argc, char *argv[]) {
    clock_t start = clock();

    int opt;
    char* bytecode_file = NULL;
    char* language_file = NULL;

    if ((opt = getopt(argc, argv, "b:l:v")) != -1) {
        switch (opt) {
            case 'b':
                // Option for using the runtime through a bytecode file
                bytecode_file = optarg;
                break;
            case 'l':
                // Option for compiling down to a bytecode file
                language_file = optarg;
                break;
            case 'v':
                // In this case, -v is used to display the version of the runtime
                printf("RVMC Version: %d.%d\n", IL_MAJOR_VERSION, IL_MINOR_VERSION);
                printf("This is the version of the runtime and compiled bytecode file  \n");
                return 0;
            default:
                fprintf(stderr, "Usage: %s [-b bytecode_file] [-l language_file] [-v] \n", argv[0]);
                return 1;
        }
    }

    if (bytecode_file != NULL && language_file != NULL) {
        fprintf(stderr, "Cannot specify both bytecode and langauge representation files\n");
        return 1;
    }

    if (bytecode_file == NULL && language_file == NULL) {
        fprintf(stderr, "No language file specified. Please specify a bytecode or language file. \n");
        exit(EXIT_FAILURE);
    }

    #if FEATURE_FLAG_NEW_PARSER == 1
    // Using the new parser
    FILE *file = NULL;

    if (language_file != 0) {
        if (argc > 1) {
            file = fopen(language_file, "r");
            if (!file) {
                perror(argv[1]);
                return 1;
            }
            yyin = file;
        }

        if (yyparse() == 0) {
            char *directory;
            char *name;
            gen_save_location(language_file, &directory, &name);
            // construct_class_file(root, NULL);
            // save_class_file(directory, name);
        }
        free_node(root);
        yylex_destroy();
        fclose(file);
    } else if (bytecode_file != 0) {
        // Feature flag is set - use the new parser (from preprocessor if-statemnet)
        ClassFile* class = load_class_file(bytecode_file);
        if (!class) {
            fprintf(stderr, "Failed to load class file: %s \n", bytecode_file);
            return 1;
        }
        free(class);
        return 1;
    } else {
        fprintf(stderr, "No file specified");
        return 1;
    }

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

    clock_t end = clock();

    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Completed in: %.6f seconds\n", elapsed);

    return 0;
}
