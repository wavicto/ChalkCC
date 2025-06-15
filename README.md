# chalkcc

chalkcc is a compiler for a subset of C written in C++.

chalkcc targets x86 compatible assembly. It is a toy compiler written for an educational purpose.

chalkcc currently supports compilation for: a main function, return statements, constants, unary operators (negation and complement), and binary operators (addition, subtraction, multiplication, division, and modulus).

Functionality in progress: local variables and logical expressions

# Pipeline
Lexer: takes a file and produces a list of tokens
Parser: creates an Abstract Syntax Tree (AST) from the tokens.  Recursive descent parser with precedence climbing
Three address code (TAC) intermediate representation: 
Codegen: breaks down the TAC IR even further. traverses this structure to generate assembly.
# Build Instructions

To compile: make
./compile [input file] -flags

# References

//https://www.cs.princeton.edu/~appel/papers/asdl97.pdf
//https://hillside.net/plop/plop2003/Papers/Jones-ImplementingASTs.pdf
Book citation by sandra nora, writing a C compiler.