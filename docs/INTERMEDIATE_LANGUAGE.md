# Intermediate Language

This documents the bytecode `.class` files that is an intermediate representation of this language, more suitable for use in direct machine code (but abstracted out to run through the virtual machine that was created).

This intermediate language and representation was inspired by Java and the `Java Intermediate Language (JIL)` and `Common Intermediate Language (CIL)`.

The development of this project began with the intermediate language before a higher level representation will be created and generate this representation that the virtual machine runs.

1. Source code is converted to bytecode (TODO)
2. Ahead-of-time compilation is completed. Potentially this project will extend to introduce a just-in-time (JIT) compiler.
3. Computer process executes the native code that the virtual machine calls

## Computational Model
The byteocde representation of this language is stack-based (similar to the CIL from C#). There are no virtualized registers.

This differs from x86 assembly language one might be used to where registers are referenced in add instructions.
In x86 assembly:
```assembly
add aex, edx
```

In the intermediate language:
```assembly
STORE_VAR 0
STORE_VAR 1
ADD
```

Notice that `ADD` contains zero parameters. Instead, it is grabbing the two values on the top of the stack.

The result is then also added back onto the stack.

## Implementation Notes and Sources
https://en.wikipedia.org/wiki/Common_Intermediate_Language
