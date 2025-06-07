#ifndef CODEGEN_HPP    
#define CODEGEN_HPP

#include "asm_node.hpp"
#include "parser.hpp"
#include "asm_visitor.hpp"

class ASM_AST {
    public:

    ASM_AST(AST &tree);

    ~ASM_AST();

    //generates asm from AST
    void asm_gen();

    private:
    asm_program* root;

    asm_program* gen(program* node);
    asm_function* gen(function* node);
    asm_instruction* gen(statement* node);
    asm_instruction* gen(expression* node);
};

#endif