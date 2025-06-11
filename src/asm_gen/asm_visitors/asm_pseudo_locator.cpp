#include "asm_gen/asm_visitors/asm_pseudo_locator.hpp"
#include "asm_gen/asm_node.hpp"

asm_pseudo_locator::asm_pseudo_locator(std::unordered_map<asm_pseudo_reg*, int> &map)
    :pseudo_map(map){}

void asm_pseudo_locator::visit(asm_program* node) {
    asm_function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void asm_pseudo_locator::visit(asm_function* node) {
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
}

void asm_pseudo_locator::visit(asm_mov* node) {
    asm_operand* src = node->src;
    asm_operand* dst = node->dst;
    if (auto pseudo = dynamic_cast<asm_pseudo_reg*>(src)) {
        stack_location* location = new stack_location;
        location->rbp_offset = pseudo_map[pseudo];
        node->src = location;
    }
    else if (src){
        src->accept(this);
    }

    if (auto pseudo = dynamic_cast<asm_pseudo_reg*>(dst)) {
        stack_location* location = new stack_location;
        location->rbp_offset = pseudo_map[pseudo];
        node->dst = location;    
    }
    else if (dst){
        dst->accept(this);
    }
}

void asm_pseudo_locator::visit(asm_unary* node) {
    asm_operand* operand = node->operand_ptr;
    if (auto pseudo = dynamic_cast<asm_pseudo_reg*>(operand)) {
        stack_location* location = new stack_location;
        location->rbp_offset = pseudo_map[pseudo];
        node->operand_ptr = location; 
    }
    else if (operand){
        operand->accept(this);
    }
}

void asm_pseudo_locator::visit(asm_ret* node) {}
void asm_pseudo_locator::visit(allocate_stack* node) {}
void asm_pseudo_locator::visit(asm_reg* node) {}
void asm_pseudo_locator::visit(asm_imm* node) {}
void asm_pseudo_locator::visit(asm_pseudo_reg* node) {}
void asm_pseudo_locator::visit(stack_location* node) {}

