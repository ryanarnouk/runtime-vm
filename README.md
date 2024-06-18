# Runtime VM

- Inspired by the C# Runtime and Java Virtual Machine (JVM)

Features:
- class loader (class definition of a file)
- interpreter (maybe?)
- stack_vm.c
- lexer (maybe?)
- gc (gc.c and gc.h)
  - reference counting (most likely, am fine with the reference overhead)
  - To consider: mark-and-sweep (good for complex object graphs with circular references but it takes occassional pauses to go through and do). More robust: mark and sweep
  - Performance: manage a large heap and want to avoid the overhead of frequent updates, mark and sweep might be more efficient overall
  - Java uss Marking for what it's worth

- parser


TODO:
- Discuss the intermediate representation of the language (similar to the Common Intermediate Language in C# (CIL))
