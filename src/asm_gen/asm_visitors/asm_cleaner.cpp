#include "asm_gen/asm_visitors/asm_cleaner.hpp"
#include "asm_gen/asm_node.hpp"

void asm_cleaner::visit(asm_program* node){
    asm_function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void asm_cleaner::visit(asm_function* node){
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    delete node;
}

void asm_cleaner::visit(asm_mov* node){
    asm_operand* src = node->src;
    asm_operand* dst = node->dst;
    if (src){
        src->accept(this);
    }
    if (dst){
        dst->accept(this);
    }
    delete node;
}

void asm_cleaner::visit(asm_unary* node){
    asm_operand* op_ptr = node->operand_ptr;
    if (op_ptr){
        op_ptr->accept(this);
    }
    delete node;
}

void asm_cleaner::visit(asm_ret* node){delete node;}
void asm_cleaner::visit(allocate_stack* node){delete node;}
void asm_cleaner::visit(asm_pseudo_reg* node){delete node;}
void asm_cleaner::visit(stack_location* node){delete node;}
void asm_cleaner::visit(asm_reg* node){delete node;}
void asm_cleaner::visit(asm_imm* node){delete node;}
