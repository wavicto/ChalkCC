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
    //Multiple scratch register are dynamically created since nodes are cleaned up recursively
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

//Add and sub instructions can't have memory addresses as both operands
//Multiplication can't have memory addresses as its dst operand
void AsmInstructionFinalizer::visit(AsmBinary* node) {
    auto src = dynamic_cast<StackLocation*>(node->src);
    auto dst = dynamic_cast<StackLocation*>(node->dst);

    if (node->op == Mult){
        //I may add constructors to the nodes, but I also want to keep their POD-likeness
        if (dst != nullptr){
            AsmReg* scratch_one = new AsmReg;
            scratch_one->name = R11;
            AsmReg* scratch_two = new AsmReg;
            scratch_two->name = R11;
            AsmReg* scratch_three = new AsmReg;
            scratch_three->name = R11;
    
            AsmMov* mov_1 = new AsmMov;
            mov_1->src = node->dst;
            mov_1->dst = scratch_one;

            node->dst = scratch_two;
        
            AsmMov* mov_2 = new AsmMov;
            mov_2->src = scratch_three;
            mov_2->dst = mov_1->src;
            //problem here^^

            //Replaces instructions in the list
            for (auto it = instructions->begin(); it != instructions->end(); ++it){
                if (*it == node){
                    it = instructions->insert(it, mov_1);
                    it++;
                    it++;
                    instructions->insert(it, mov_2);
                    break;
                }
            }
        }
    }
    else if (node->op == Sub || node->op == Add){
        if (src != nullptr && dst != nullptr){
            AsmReg* scratch_one = new AsmReg;
            scratch_one->name = R10;
            AsmReg* scratch_two = new AsmReg;
            scratch_two->name = R10;
            
            AsmMov* mov = new AsmMov;
            mov->src = src;
            mov->dst = scratch_one;
            node->src = scratch_two;

            for (auto it = instructions->begin(); it != instructions->end(); ++it){
                if (*it == node){
                    instructions->insert(it, mov);
                    break;
                }
            }
        }
    }
    else {
        throw std::runtime_error("AsmBinary Expected: Mult, Sub, or Add");
    }
}

//Idiv can not act on constants. We copy constants into a 
//scratch register for when idiv needs to act on a value
void AsmInstructionFinalizer::visit(Idiv* node) {
    auto operand = dynamic_cast<AsmImm*>(node->operand_ptr);
    if (operand != nullptr){
        AsmReg* scratch_one = new AsmReg;
        scratch_one->name = R10;
        AsmReg* scratch_two = new AsmReg;
        scratch_two->name = R10;

        AsmMov* mov = new AsmMov;
        mov->src = node->operand_ptr;
        mov->dst = scratch_one;
        node->operand_ptr = scratch_two;

    for (auto it = instructions->begin(); it != instructions->end(); ++it){
        if (*it == node){
            instructions->insert(it, mov);
            break;
        }
    }
    }
}

void AsmInstructionFinalizer::visit(Cdq* node) {}
void AsmInstructionFinalizer::visit(AsmRet* node) {}
void AsmInstructionFinalizer::visit(AsmUnary* node) {}
void AsmInstructionFinalizer::visit(StackAllocate* node) {}
void AsmInstructionFinalizer::visit(AsmReg* node) {}
void AsmInstructionFinalizer::visit(AsmImm* node) {}
void AsmInstructionFinalizer::visit(AsmPseudoReg* node) {}
void AsmInstructionFinalizer::visit(StackLocation* node) {}