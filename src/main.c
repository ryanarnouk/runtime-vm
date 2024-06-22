#include <stdio.h>
#include <stdlib.h>
#include "arc.h"
#include "bytecode.h"
#include "class.h"
#include "stack_vm.h"

int main() {
    Class* class = load_class("examples/main.class");
    if (!class) {
        return 1;
    }

    VirtualMachine* vm = vm_init();
    Method* main_method = &class->methods[0];
    printf("Executing method: %s \n", main_method->name);
    execute_bytecode(vm, main_method->bytecode, main_method->bytecode_length);

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

    clean_class(class);
    vm_free(vm);

    return 0;
}
