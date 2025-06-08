#include "asm_node.hpp"
#include "asm_visitor.hpp"

asm_visitor::~asm_visitor() {}

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

void asm_cleaner::visit(asm_ret* node){
    delete node;
}

void asm_cleaner::visit(asm_unary* node){
    asm_operand* op_ptr = node->operand_ptr;
    if (op_ptr){
        op_ptr->accept(this);
    }
    delete node;
}

void asm_cleaner::visit(allocate_stack* node){
    delete node;
}

void asm_cleaner::visit(asm_pseudo_reg* node){
    delete node;
}

void asm_cleaner::visit(stack_location* node){
    delete node;
}

void asm_cleaner::visit(asm_reg* node){
    delete node;
}

void asm_cleaner::visit(asm_imm* node){
    delete node;
}

/*
void asm_generator::visit(asm_program* node){
    file.open("assembly.s");
    asm_function* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    file << ".section .note.GNU-stack,\"\",@progbits" << std::endl;
}

void asm_generator::visit(asm_function* node){
    file << ".global " << node->name << std::endl;
    file << node->name << ":" << std::endl;
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    file << std::endl;
}

void asm_generator::visit(asm_instruction* node){
    asm_instruction* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void asm_generator::visit(asm_mov* node){
    file << "\tmovl ";
    if (node->src){
        node->src->accept(this);
        file << ", ";
    }
    if (node->dst){
        node->dst->accept(this);
        file << std::endl;
    }
}

void asm_generator::visit(asm_ret* node){
    file << "\tret ";
}

void asm_generator::visit(asm_operand* node){
    asm_operand* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void asm_generator::visit(asm_reg* node){
    switch(node->name){
        case 0:
            file << "%eax";
            break;
    }
}

void asm_generator::visit(asm_imm* node){
    file << "$" << node->value;
}
*/
