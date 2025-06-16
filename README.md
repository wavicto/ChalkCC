# chalkcc

**chalkcc** is a compiler for a subset of C, implemented in C++.

It is a toy compiler written for educational purposes, targeting **x86-compatible assembly**.

## Supported Features

**chalkcc** currently supports: 
- Main functions
- Return statements
- Constants
- Unary operators:
    - Negation `-`
    - Bitwise complement `~`
- Binary operators:
    - Addition `+`
    - Subtraction `-`
    - Multiplication `*`
    - Division `/`
    - Modulus `%`

Work in Progress: 
- Local variables
- Logical expressions

## Build Instructions

To build **chalkcc**:
```bash
make
```
To build tests:
```bash
make test
```
To delete executables:
```bash
make clean
```
To compile a source file:
```bash
./compile [input_file] [flags]
```
flags:
- `-lex`       Run the lexer. Displays the tokens generated.
- `-parse`     Run the lexer and parser. Displays C AST.
- `-codegen`   Run the lexer, parser, and generate assembly file. Stops before executable generation.

## Design and Architecture

### Compiler Pipeline

1. **Lexer**

Reads a source file and produces a list of tokens.

2. **Parser**

Builds an Abstract Syntax Tree (AST) from tokens using a recursive descent parser with precedence climbing.

3. **Three-Address Code (TAC) IR** 

Produces an intermediate representation from the AST using TAC to simplify analysis and code generation.

4. **Code Generation**

Breaks down the TAC IR further and traverses the structure to generate x86-compatible assembly.

### Visitor Pattern

**chalkcc** employs the **Visitor Pattern** to traverse and operate upon the nodes of its various structures (AST, IR, etc), allowing chosen functionality to be implemented without modifying the nodes themselves.

## References
Jones, J. (2003). Abstract Syntax Tree Implementation Idioms. In *Proceedings of the 10th Conference
    on Pattern Languages of Programs (PLoP2003)*. Retrieved from
    http://www.hillside.net/plop/plop2003/Papers/Jones-ImplementingASTs.pdf

Sandler, N. (2024). *Writing a C Compiler: Build a Real Programming Language From Scratch*. No Starch
    Press. ISBN 978-1718500426

Wang, D. C., Appel, A. W., Korn, J. L., & Serra, C. S. (1997). The Zephyr Abstract Syntax
    Description Language. In *Proceedings of the Conference on Domain-Specific Languages (DSL'97)*
    (p. 17). USENIX Association.
