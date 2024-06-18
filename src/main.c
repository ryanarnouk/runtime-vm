#include <stdio.h>
#include <stdlib.h>
#include "bytecode.h"
#include "class.h"
#include "stack_vm.h"

int main() {
    Class* class = load_class("examples/main.class");
    if (!class) {
        return 1;
    }

    vm_init();
    Method* main_method = &class->methods[0];
    printf("Executing method: %s \n", main_method->name);
    execute_bytecode(main_method->bytecode, main_method->bytecode_length);

    clean_class(class);

    return 0;
}
