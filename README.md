# Runtime VM

This project is inspired by the C# Runtime and Java Virtual Machine (JVM). It also draws on inspiration from Swift, C++, and Rust for basic memory management techniques.

This project is currently in development stages. But eventually, my hope is it to be a very basic rendition of a runtime and virtual machine that can run a simple language. It will not be fully-fledged out, but it will be a good starting point for me to learn about how these runtimes work.

More concretely, my goal is to be able to do simple Leetcode problems using this runtime and language.

## Future Plans
My plan is eventually implement my own language for the runtime. It would include a lexer that tokenizes the input source code and a parser that converts tokens into an Abstract Syntax Tree (AST) which eventually gets converted into bytecode. This is not the traditional approach that other runtimes like the JVM follow which runs the bytecode directly (instead compiling it to the bytecode in an early step before the runtime starts). To simplify the project and use a single codebase, I will provide the option for the runtime to execute bytecode directly and the option for the runtime to encompass both steps and allow it to take in the new language directly. Note that this approach will slow down runtime to provide time to do the parsing/lexing.

## Setup
- A C compiler is required to compile the project. I use `gcc` on my machine and in the Makefile.

In the root directory:
```
make
```

Run the basic example:
```
./bin/runtime -b examples/basic/main.class
```
