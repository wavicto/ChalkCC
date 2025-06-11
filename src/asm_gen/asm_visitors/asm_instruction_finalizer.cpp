#include "asm_gen/asm_visitors/asm_instruction_finalizer.hpp"
#include "asm_gen/asm_node.hpp"

AsmInstructionFinalizer::AsmInstructionFinalizer(int size)
    : stack_size(size) {}

void AsmInstructionFinalizer::visit(AsmProgram* node) {
    AsmFunction* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void AsmInstructionFinalizer::visit(AsmFunction* node) {
    instructions = &(node->instructions);
    auto saved_instructions = *instructions; 
    StackAllocate* stack_allocator = new StackAllocate;
    stack_allocator->size = abs(stack_size);
    for (auto ptr : saved_instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    //Adds allocate stack instruction
    instructions->insert(instructions->begin(), stack_allocator);
}

void AsmInstructionFinalizer::visit(AsmMov* node) {
    auto src = dynamic_cast<StackLocation*>(node->src);
    auto dst = dynamic_cast<StackLocation*>(node->dst);

    //Determines if the mov instruction has both operands as stack locations
    //If so, remove said mov instruction and then adds two new mov instructions using R10D as scratch reg
    if (src != nullptr && dst != nullptr){
        AsmReg* scratch_one = new AsmReg;
        scratch_one->name = R10;
        AsmReg* scratch_two = new AsmReg;
        scratch_two->name = R10;

        AsmMov* mov_1 = new AsmMov;
        mov_1->src = node->src;
        mov_1->dst = scratch_one;
    
        AsmMov* mov_2 = new AsmMov;
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

void AsmInstructionFinalizer::visit(AsmRet* node) {}
void AsmInstructionFinalizer::visit(AsmUnary* node) {}
void AsmInstructionFinalizer::visit(StackAllocate* node) {}
void AsmInstructionFinalizer::visit(AsmReg* node) {}
void AsmInstructionFinalizer::visit(AsmImm* node) {}
void AsmInstructionFinalizer::visit(AsmPseudoReg* node) {}
void AsmInstructionFinalizer::visit(StackLocation* node) {}