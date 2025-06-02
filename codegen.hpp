#ifndef CODEGEN_HPP    
#define CODEGEN_HPP

#include "asm_node.hpp"
#include "parser.hpp"
#include "visitor.hpp"

class ASM_AST {
    public:

    ASM_AST(AST &tree);

    ~ASM_AST();

    private:
    asm_program* root;
};

#endif