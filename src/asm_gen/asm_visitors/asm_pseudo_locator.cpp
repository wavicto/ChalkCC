#include "asm_gen/asm_visitors/asm_pseudo_locator.hpp"
#include "asm_gen/asm_node.hpp"

AsmPseudoLocator::AsmPseudoLocator(std::unordered_map<std::shared_ptr<AsmPseudoReg>, int> &map)
    :pseudo_map(map){}

void AsmPseudoLocator::visit(AsmProgram* node) {
    if (node->func_ptr){
        node->func_ptr->accept(this);
    }
}

void AsmPseudoLocator::visit(AsmFunction* node) {
    for (const auto &ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
}

//Replaces pseudo registers with an actual stack location
//Pseudo register dynamic memory is handled by the AsmAST as a whole
void AsmPseudoLocator::visit(AsmMov* node) {
    if (auto pseudo = std::dynamic_pointer_cast<AsmPseudoReg>(node->src)) {
        auto location = std::make_shared<StackLocation>();
        location->rbp_offset = pseudo_map[pseudo];
        node->src = location;
    }
    else if (node->src){
        node->src->accept(this);
    }

    if (auto pseudo = std::dynamic_pointer_cast<AsmPseudoReg>(node->dst)) {
        auto location = std::make_shared<StackLocation>();
        location->rbp_offset = pseudo_map[pseudo];
        node->dst = location;    
    }
    else if (node->dst){
        node->dst->accept(this);
    }
}

void AsmPseudoLocator::visit(AsmUnary* node) {
    if (auto pseudo = std::dynamic_pointer_cast<AsmPseudoReg>(node->operand_ptr)) {
        auto location = std::make_shared<StackLocation>();
        location->rbp_offset = pseudo_map[pseudo];
        node->operand_ptr = location; 
    }
    else if (node->operand_ptr){
        node->operand_ptr->accept(this);
    }
}

void AsmPseudoLocator::visit(AsmBinary* node) {
    if (auto pseudo = std::dynamic_pointer_cast<AsmPseudoReg>(node->src)) {
        auto location = std::make_shared<StackLocation>();
        location->rbp_offset = pseudo_map[pseudo];
        node->src = location; 
    }
    else if (node->src){
        node->src->accept(this);
    }

    if (auto pseudo = std::dynamic_pointer_cast<AsmPseudoReg>(node->dst)) {
        auto location = std::make_shared<StackLocation>();
        location->rbp_offset = pseudo_map[pseudo];
        node->dst = location; 
    }
    else if (node->dst){
        node->dst->accept(this);
    }
}

void AsmPseudoLocator::visit(Idiv* node) {
    if (auto pseudo = std::dynamic_pointer_cast<AsmPseudoReg>(node->operand_ptr)) {
        auto location = std::make_shared<StackLocation>();
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

