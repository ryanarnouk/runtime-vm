# Stack Architecture

## Computational Model

The bytecode intermediate language representation is object-oriented and stack-based (similar to the CIL from C#). Instruction parameters and results are all stored on a single stack and not in any virtualized registers.

## Stack Architecture

I opted to avoid using virtualized registers to match more closely to the JVM. A stack-based architecture also seemed easier to implement with less bytecode parsing and simplified instruction sets.

TODO... add more
