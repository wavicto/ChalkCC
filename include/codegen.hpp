#ifndef CODEGEN_HPP    
#define CODEGEN_HPP

#include "asm_node.hpp"
#include "tac_ast.hpp"
#include "asm_visitor.hpp"

class ASM_AST {
    public:

    ASM_AST(AST &tree);

    ~ASM_AST();

    //generates asm from AST
    void asm_gen();

    private:
    asm_program* root;

    asm_program* gen(tac_program* node);
    asm_function* gen(tac_function* node);
    void gen(tac_return* node, std::vector <asm_instruction*> &instructions);
    void gen(tac_unary* node, std::vector <asm_instruction*> &instructions);
    asm_operand* gen(tac_constant* node);
    asm_operand* gen(tac_var* node);

    friend class tac_return;
    friend class tac_unary;
    friend class tac_constant;
    friend class tac_var;
};

#endif