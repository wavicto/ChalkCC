#include "asm_gen/asm_visitors/asm_generator.hpp"
#include "asm_gen/asm_node.hpp"

void asm_generator::visit(asm_program* node){
    file.open("assembly.s");
    asm_function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    file << ".section .note.GNU-stack,\"\",@progbits" << std::endl;
}

void asm_generator::visit(asm_function* node){
    file << ".global " << node->name << std::endl;
    file << node->name << ":" << std::endl;
    file << "\tpushq\t%rbp" << std::endl;
    file << "\tmovq\t%rsp, %rbp" << std::endl;
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    file << std::endl;
}

void asm_generator::visit(asm_mov* node){
    file << "\tmovl\t";
    if (node->src){
        node->src->accept(this);
        file << ", ";
    }
    if (node->dst){
        node->dst->accept(this);
        file << std::endl;
    }
}

void asm_generator::visit(asm_unary* node){
    if (node->op == Not){
        file << "\tnotl\t";
    }
    else if (node->op == Neg){
        file << "\tnegl\t";
    }
    if (node->operand_ptr){
        node->operand_ptr->accept(this);
    }
    file << std::endl;
}

void asm_generator::visit(allocate_stack* node){
    file << "\tsubq\t$" << node->size << ", %rsp" << std::endl;
}

void asm_generator::visit(asm_ret* node){
    file << "\tmovq\t%rbp, %rsp" << std::endl;
    file << "\tpopq\t%rbp" << std::endl;
    file << "\tret ";
}

void asm_generator::visit(asm_reg* node){
    switch(node->name){
        case 0:
            file << "%eax";
            break;
        case 1: 
            file << "%r10d";
    }
}

void asm_generator::visit(stack_location* node){
    file << node->rbp_offset << "(%rbp)";
}

void asm_generator::visit(asm_imm* node){
    file << "$" << node->value;
}

void asm_generator::visit(asm_pseudo_reg* node){}