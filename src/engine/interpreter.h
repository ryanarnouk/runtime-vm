#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../bytecode.h"
#include "../stack_vm.h"
#include <complex.h>
#include <stdio.h>

void execute_bytecode(VirtualMachine* vm, Bytecode* bytecode, int length);

#endif
