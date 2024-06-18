#include "bytecode.h"
#include <complex.h>
#include <stdio.h>
#include "stack_vm.h"

void execute_bytecode(Bytecode *bytecode, int length) {
    int pc = 0; // program counter

    while (pc < length) {
        Bytecode bc = bytecode[pc];
        switch(bc.instruction) {
            case LOAD_CONST:
                vm_push(bc.operand);
                break;
            case STORE_VAR:
                vm.vars[bc.operand] = vm_pop();
                break;
            case ADD:
                vm.stack[vm.sp - 1] = vm.stack[vm.sp - 1] + vm.stack[vm.sp];
                vm.sp--;
                break;
            case SUB:
                vm.stack[vm.sp - 1] = vm.stack[vm.sp - 1] - vm.stack[vm.sp];
                vm.sp--;
                break;
            case JE:
                if (vm_pop() == 0) {
                    pc += bc.operand - 1;
                }
                break;
            case PRINT:
                //stack_print();
                printf("%d\n", vm_pop());
                break;
            default:
                fprintf(stderr, "Unknown instruction: %d\n", bc.instruction);
                break;
        }
        pc++;
    }
}
