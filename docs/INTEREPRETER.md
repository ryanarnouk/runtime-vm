# Interpreter

This bytecode runtime virtual machine does not contain just-in-time compilation (JIT) or ahead-of-time compilation. Instead, it interprets the bytecode directly. This can be observed in the `execute_bytecode` function in `src/bytecode.c`.

Eventually, I may work on a JIT compiler or ahead-of-time (AOT) compilation for the `arm64` architecture.
