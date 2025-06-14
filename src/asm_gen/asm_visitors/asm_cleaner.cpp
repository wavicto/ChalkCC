#include "asm_gen/asm_visitors/asm_cleaner.hpp"
#include "asm_gen/asm_node.hpp"

void AsmCleaner::visit(AsmProgram* node){
    AsmFunction* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void AsmCleaner::visit(AsmFunction* node){
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    delete node;
}

void AsmCleaner::visit(AsmMov* node){
    AsmOperand* src = node->src;
    AsmOperand* dst = node->dst;
    if (src){
        src->accept(this);
    }
    if (dst){
        dst->accept(this);
    }
    delete node;
}

void AsmCleaner::visit(AsmUnary* node){
    AsmOperand* op_ptr = node->operand_ptr;
    if (op_ptr){
        op_ptr->accept(this);
    }
    delete node;
}

void AsmCleaner::visit(AsmBinary* node){
   if (node->src){
    (node->src)->accept(this);
   }
   if (node->dst){
    (node->dst)->accept(this);
   }
   delete node;
}

void AsmCleaner::visit(Idiv* node){
    AsmOperand* op_ptr = node->operand_ptr;
    if (op_ptr){
        op_ptr->accept(this);
    }
    delete node;
}

void AsmCleaner::visit(AsmRet* node){delete node;}
void AsmCleaner::visit(StackAllocate* node){delete node;}
void AsmCleaner::visit(AsmPseudoReg* node){delete node;}
void AsmCleaner::visit(StackLocation* node){delete node;}
void AsmCleaner::visit(AsmReg* node){delete node;}
void AsmCleaner::visit(AsmImm* node){delete node;}
void AsmCleaner::visit(Cdq* node){delete node;}
