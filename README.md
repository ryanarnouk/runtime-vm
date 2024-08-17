# Runtime VM

This project is inspired by the C# Runtime and Java Virtual Machine (JVM). It also draws on inspiration from Swift, C++, and Rust for basic memory management techniques.

This project is currently in development stages. But eventually, my hope is it to be a very basic rendition of a runtime and virtual machine that can run a simple language. It will not be fully-fledged out, but it will be a good starting point for me to learn about how these runtimes work.

More concretely, my goal is to be able to do simple Leetcode problems using this runtime and language.

## Future Plans
I am currently working on a rewrite of the original functionality, this time involving the implementation of my own language for the runtime. This has been developed with Flex and Bison, providing a lexer that tokenizes the input source code and a parser that converts tokens into an Abstract Syntax Tree (AST) which I am working to convert to gets converted into bytecode.

This means that the project is not only a runtime/VM. It contains a "compilation" into this bytecode and a runtime for the bytecode (all under the runtime repo).


## Setup
- A C compiler is required to compile the project. I use Clang on my machine. Note that the Makefile references `gcc`, but a symlink should exist to point to Clang instead.

1. Clone project

2. In the root directory:
```
make
```

3. Optional
You can reference `./bin/runtime` to run the project (from within the repo directly). However, to add the symlink to your PATH environment variable and create the option to run `rvm` directly, execute the following after granting execute permissions:

```
./env_setup.sh
```

## Usage

There are three ways to use the project

### Compilation
This stage takes a language file (`.rvm` extension) and generates a binary-encoded compiled file that uses the RVM bytecode. This file is generated with the same file name and in the same directory as the input file, with the `.rvmc` extension. It is versioned.

Example
```
rvm -l <path_to_rvm_file>
```
> Replace `rvm` with the path to the `/bin/runtime` executable if you did not set up RVM in your PATH env variable

The "c" at the end of the file extension stands for "Class", inspired by Java's bytecode files being labelled with a `.class` file extension.


### Runtime
This stage takes the binary-encoded `rvmc` file and runs the virtual stack machine/runtime, interpreting the language

```
rvm -b <path_to_rvmc_file>
```

### Version
To view your current version of the runtime and the encoding/structure of the class files run:

```
rvm -v
```

# Further

While a not so creative name, RVM serves a second purpose as a play on Research in Motion's acronym (RIM) - fitting since this project was also developed in Canada :)
