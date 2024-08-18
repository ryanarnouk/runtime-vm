#include "interpreter.h"

#if FEATURE_FLAG_NEW_PARSER == 0

void execute_bytecode(VirtualMachine* vm, Bytecode *bytecode, int length) {
    int pc = 0; // program counter

    while (pc < length) {
        Bytecode bc = bytecode[pc];
        switch(bc.instruction) {
            case LOAD_CONST:
                vm_push(vm, bc.operand);
                break;
            case STORE_VAR:
                vm->vars[bc.operand] = vm_pop(vm);
                break;
            case ADD:
                vm->stack[vm->sp - 1] = vm->stack[vm->sp - 1] + vm->stack[vm->sp];
                vm->sp--;
                break;
            case SUB:
                vm->stack[vm->sp - 1] = vm->stack[vm->sp - 1] - vm->stack[vm->sp];
                vm->sp--;
                break;
            case JE:
                if (vm_pop(vm) == 0) {
                    pc += bc.operand - 1;
                }
                break;
            case PRINT:
                //stack_print();
                printf("%d\n", vm_pop(vm));
                break;
            default:
                fprintf(stderr, "Unknown instruction: %d\n", bc.instruction);
                break;
        }
        pc++;
    }
}

#endif
