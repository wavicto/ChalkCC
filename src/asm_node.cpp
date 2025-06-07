#include "asm_node.hpp"

ASMNode::~ASMNode(){}

void asm_program::accept(asm_visitor* v){
    v->visit(this);
}

void asm_function::accept(asm_visitor* v){
    v->visit(this);
}

void asm_instruction::accept(asm_visitor* v){
    v->visit(this);
}

void asm_mov::accept(asm_visitor* v){
    v->visit(this);
}

void asm_ret::accept(asm_visitor* v){
    v->visit(this);
}

void asm_operand::accept(asm_visitor* v){
    v->visit(this);
}

void asm_reg::accept(asm_visitor* v){
    v->visit(this);
}

void asm_imm::accept(asm_visitor* v){
    v->visit(this);
}