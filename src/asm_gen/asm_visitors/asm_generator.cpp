#include "asm_gen/asm_visitors/asm_generator.hpp"
#include "asm_gen/asm_node.hpp"

void AsmGenerator::visit(AsmProgram* node){
    file.open("assembly.s");
    AsmFunction* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    file << ".section .note.GNU-stack,\"\",@progbits" << std::endl;
}

void AsmGenerator::visit(AsmFunction* node){
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

void AsmGenerator::visit(AsmMov* node){
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

void AsmGenerator::visit(AsmUnary* node){
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

void AsmGenerator::visit(AsmBinary* node){
    if (node->op == Mult){
        file << "\timull\t";
    }
    else if (node->op == Add){
        file << "\taddl\t";
    }
    else if (node->op == Sub){
        file << "\tsubl\t";
    }
    if (node->src){
        node->src->accept(this);
    }
    file << ", ";
    if (node->dst){
        node->dst->accept(this);
    }
}

void AsmGenerator::visit(Idiv* node){
    file << "\tidivl\t";
    if (node->operand_ptr){
        node->operand_ptr->accept(this);
    }
}

void AsmGenerator::visit(Cdq* node){
    file << "cdq" << std::endl;
}

void AsmGenerator::visit(StackAllocate* node){
    file << "\tsubq\t$" << node->size << ", %rsp" << std::endl;
}

void AsmGenerator::visit(AsmRet* node){
    file << "\tmovq\t%rbp, %rsp" << std::endl;
    file << "\tpopq\t%rbp" << std::endl;
    file << "\tret ";
}

void AsmGenerator::visit(AsmReg* node){
    switch(node->name){
        case 0:
            file << "%eax";
            break;
        case 1: 
            file << "%r10d";
    }
}

void AsmGenerator::visit(StackLocation* node){
    file << node->rbp_offset << "(%rbp)";
}

void AsmGenerator::visit(AsmImm* node){
    file << "$" << node->value;
}

void AsmGenerator::visit(AsmPseudoReg* node){}