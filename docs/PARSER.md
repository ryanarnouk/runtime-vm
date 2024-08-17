# Parser

This project uses flex and yacc/bison for the language parser.

Flex:
> Fast lexical analyzer generator

Bison:
> Serves as a replacement for Yacc (while the files are still stored under a `.y` file extension)

Bytecode binary-encoded representations of the intermediate language are stored with `.rvmc` extension.
High-level human-readable language representations are using `.rvm`

I plan to write a disassembler to show the binary files in a human-readable format similar to the `javap` command.
