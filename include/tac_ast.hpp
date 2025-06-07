#ifndef TAC_TREE_HPP    
#define TAC_TREE_HPP

#include "tac_node.hpp"
#include "tac_visitor.hpp"
#include "parser.hpp"

class TAC_AST {
    public:

    TAC_AST(AST &tree);

    ~TAC_AST();

    //generates asm from AST
    void tac_gen();

    private:
    tac_program* root;

    tac_program* gen(program* node);
    tac_function* gen(function* node);
    tac_instruction* gen(statement* node);
    tac_instruction* gen(expression* node);
};

#endif