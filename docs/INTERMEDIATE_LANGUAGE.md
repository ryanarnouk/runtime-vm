# Intermediate Language

This documents the bytecode `.class` files that is an intermediate representation of this language, more suitable for use in direct machine code (but abstracted out to run through the virtual machine that was created).

This intermediate language and representation was inspired by Java and the `Java Intermediate Language (JIL)` and `Common Intermediate Language (CIL)`.

The development of this project began with the intermediate language before a higher level representation will be created and generate this representation that the virtual machine runs.

1. Source code is converted to bytecode (TODO)
2. Ahead-of-time compilation is completed. Potentially this project will extend to introduce a just-in-time (JIT) compiler.
3. Computer process executes the native code that the virtual machine calls

## Computational Model
The bytecode representation of this language is stack-based (similar to the CIL from C#). There are no virtualized registers.

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

## JVM and CIL Inspirations
The JVM typically reduces the code more directly to "bytecode". This adds a layer of complexity for the development of the intermediate representation as more parsing and linking steps are required. The CIL is more abstracted in a representation that follows more closely to the source code that generated it.

My aim in this project is to strike a balance between an abstracted representation that is more similar to the CIL than the JVM bytecode. This means that the IR will be represented with opcodes while keeping class definitions in the same file (resulting in a mix of numerical and alphabetical characters in the bytecode). While this is technically not a "bytecode" I decided to label it as such to keep the terminology consistent with the JVM.

## CIL Representation Example
Source: https://en.wikipedia.org/wiki/Common_Intermediate_Language


Example CIL representation:
```csharp
Car myCar = new Car(1, 4);
Car yourCar = new Car(1, 3);
```

```assembly
ldc.i4.1
ldc.i4.4
newobj instance void Car::.ctor(int, int)
stloc.0    // myCar = new Car(1, 4);
ldc.i4.1
ldc.i4.3
newobj instance void Car::.ctor(int, int)
stloc.1    // yourCar = new Car(1, 3);
```

And invoking the method:
```csharp
myCar.Move(3);
```

Invoking in the CIL:
```
ldloc.0    // Load the object "myCar" on the stack
ldc.i4.3
call instance void Car::Move(int32)
```

## Runtime VM Representation

The following representation was easiest for me to implement the parser for. It models the CIL while keeping the instructions for class and object definitions simpler. My intention was to originally model it closer to the CIL but, inspired by a reponse from ChatGPT went with this more simple representation.

### Objected Oriented Programming
- `METHOD_BEGIN <method_name>`: Begins the method definition
- `METHOD_END`: Ends the method definition
- `NEW <class_name>`: Creates a new object of the class
- `DUP`: Duplicates the top of the stack
- `STORE_VAR <constant>`: Stores the top of the stack into a variable
- `INVOKE_SPECIAL <class_name> <method_name>`: Invokes a constructor method (or any other "special" method)
- `INVOKE_VIRTUAL <class_name> <method_name>`: Invokes a virtual method
- `INVOKE_STATIC <class_name> <method_name>`: Invokes a static method
- `LOAD_CONST <constant>`: Loads a constant onto the stack
- `LOAD_VAR`: Loads a variable onto the stack
- `SETFIELD fieldName`: Sets the field of an object
- `GETFIELD fieldName`: Gets the field of an object
- `RETURN`: Returns from the method

Classes are reach defined in their own `.class` files. The class file contains the class name and the fields that the class has. The fields are stored in the order they are defined in the class file. The name of the file is the name of the class.

## Implementation Notes and Sources
https://en.wikipedia.org/wiki/Common_Intermediate_Language
