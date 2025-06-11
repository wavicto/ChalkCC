#include "asm_gen/asm_visitors/asm_instruction_finalizer.hpp"
#include "asm_gen/asm_node.hpp"

asm_instruction_finalizer::asm_instruction_finalizer(int size)
    : stack_size(size) {}

void asm_instruction_finalizer::visit(asm_program* node) {
    asm_function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void asm_instruction_finalizer::visit(asm_function* node) {
    instructions = &(node->instructions);
    auto saved_instructions = *instructions; 
    allocate_stack* stack_allocator = new allocate_stack;
    stack_allocator->size = abs(stack_size);
    for (auto ptr : saved_instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    //Adds allocate stack instruction
    instructions->insert(instructions->begin(), stack_allocator);
}

void asm_instruction_finalizer::visit(asm_mov* node) {
    auto src = dynamic_cast<stack_location*>(node->src);
    auto dst = dynamic_cast<stack_location*>(node->dst);

    //Determines if the mov instruction has both operands as stack locations
    //If so, remove said mov instruction and then adds two new mov instructions using R10D as scratch reg
    if (src != nullptr && dst != nullptr){
        asm_reg* scratch_one = new asm_reg;
        scratch_one->name = R10;
        asm_reg* scratch_two = new asm_reg;
        scratch_two->name = R10;

        asm_mov* mov_1 = new asm_mov;
        mov_1->src = node->src;
        mov_1->dst = scratch_one;
    
        asm_mov* mov_2 = new asm_mov;
        mov_2->src = scratch_two;
        mov_2->dst = node->dst;

        for (auto it = instructions->begin(); it != instructions->end(); ++it){
            if (*it == node){
                it = instructions->erase(it);
                it = instructions->insert(it, mov_2);
                it = instructions->insert(it, mov_1);
                break;
            }
        }
        delete node;
    }
}

void asm_instruction_finalizer::visit(asm_ret* node) {}
void asm_instruction_finalizer::visit(asm_unary* node) {}
void asm_instruction_finalizer::visit(allocate_stack* node) {}
void asm_instruction_finalizer::visit(asm_reg* node) {}
void asm_instruction_finalizer::visit(asm_imm* node) {}
void asm_instruction_finalizer::visit(asm_pseudo_reg* node) {}
void asm_instruction_finalizer::visit(stack_location* node) {}