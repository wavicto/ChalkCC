#include "asm_gen/asm_visitors/asm_pseudo_locator.hpp"
#include "asm_gen/asm_node.hpp"

AsmPseudoLocator::AsmPseudoLocator(std::unordered_map<AsmPseudoReg*, int> &map)
    :pseudo_map(map){}

void AsmPseudoLocator::visit(AsmProgram* node) {
    AsmFunction* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void AsmPseudoLocator::visit(AsmFunction* node) {
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
}
//Replaces pseudo registers with an actual stack location
//Pseudo register dynamic memory is handled by the AsmAST as a whole
void AsmPseudoLocator::visit(AsmMov* node) {
    AsmOperand* src = node->src;
    AsmOperand* dst = node->dst;
    if (auto pseudo = dynamic_cast<AsmPseudoReg*>(src)) {
        StackLocation* location = new StackLocation;
        location->rbp_offset = pseudo_map[pseudo];
        node->src = location;
    }
    else if (src){
        src->accept(this);
    }

    if (auto pseudo = dynamic_cast<AsmPseudoReg*>(dst)) {
        StackLocation* location = new StackLocation;
        location->rbp_offset = pseudo_map[pseudo];
        node->dst = location;    
    }
    else if (dst){
        dst->accept(this);
    }
}

void AsmPseudoLocator::visit(AsmUnary* node) {
    AsmOperand* operand = node->operand_ptr;
    if (auto pseudo = dynamic_cast<AsmPseudoReg*>(operand)) {
        StackLocation* location = new StackLocation;
        location->rbp_offset = pseudo_map[pseudo];
        node->operand_ptr = location; 
    }
    else if (operand){
        operand->accept(this);
    }
}

void AsmPseudoLocator::visit(AsmBinary* node) {
    AsmOperand* src = node->src;
    AsmOperand* dst = node->dst;
    if (auto pseudo = dynamic_cast<AsmPseudoReg*>(src)) {
        StackLocation* location = new StackLocation;
        location->rbp_offset = pseudo_map[pseudo];
        node->src = location; 
    }
    else if (src){
        src->accept(this);
    }

    if (auto pseudo = dynamic_cast<AsmPseudoReg*>(dst)) {
        StackLocation* location = new StackLocation;
        location->rbp_offset = pseudo_map[pseudo];
        node->dst = location; 
    }
    else if (dst){
        dst->accept(this);
    }
}

void AsmPseudoLocator::visit(Idiv* node) {
    if (auto pseudo = dynamic_cast<AsmPseudoReg*>(node->operand_ptr)) {
        StackLocation* location = new StackLocation;
        location->rbp_offset = pseudo_map[pseudo];
        node->operand_ptr = location; 
    }
    else if (node->operand_ptr){
        node->operand_ptr->accept(this);
    }
}

void AsmPseudoLocator::visit(Cdq* node) {}
void AsmPseudoLocator::visit(AsmRet* node) {}
void AsmPseudoLocator::visit(StackAllocate* node) {}
void AsmPseudoLocator::visit(AsmReg* node) {}
void AsmPseudoLocator::visit(AsmImm* node) {}
void AsmPseudoLocator::visit(AsmPseudoReg* node) {}
void AsmPseudoLocator::visit(StackLocation* node) {}

