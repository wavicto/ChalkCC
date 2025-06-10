#include "ir_gen/tac_node.hpp"

TACNode::~TACNode(){}

void tac_program::accept(tac_visitor* v) {
    v->visit(this);
}

void tac_function::accept(tac_visitor* v) {
    v->visit(this);
}

void tac_return::accept(tac_visitor* v) {
    v->visit(this);
}

void tac_unary::accept(tac_visitor* v) {
    v->visit(this);
}

void tac_constant::accept(tac_visitor* v) {
    v->visit(this);
}

void tac_var::accept(tac_visitor* v) {
    v->visit(this);
}

void tac_return::gen(ASM_AST* tree, std::vector <asm_instruction*> &instructions){
    tree->gen(this, instructions);
}

void tac_unary::gen(ASM_AST* tree, std::vector <asm_instruction*> &instructions){
    tree->gen(this, instructions);
}

asm_operand* tac_constant::gen(ASM_AST* tree){
    return tree->gen(this);
}

asm_operand* tac_var::gen(ASM_AST* tree){
    return tree->gen(this);
}