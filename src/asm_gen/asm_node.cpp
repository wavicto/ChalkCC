#include "asm_gen/asm_node.hpp"

ASMNode::~ASMNode(){}

void asm_program::accept(asm_visitor* v){
    v->visit(this);
}

void asm_function::accept(asm_visitor* v){
    v->visit(this);
}

void asm_mov::accept(asm_visitor* v){
    v->visit(this);
}

void allocate_stack::accept(asm_visitor* v){
    v->visit(this);
}

void asm_pseudo_reg::accept(asm_visitor* v){
    v->visit(this);
}

void stack_location::accept(asm_visitor* v){
    v->visit(this);
}

void asm_unary::accept(asm_visitor* v){
    v->visit(this);
}
void asm_ret::accept(asm_visitor* v){
    v->visit(this);
}

void asm_reg::accept(asm_visitor* v){
    v->visit(this);
}

void asm_imm::accept(asm_visitor* v){
    v->visit(this);
}