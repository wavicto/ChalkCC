#include "asm_gen/asm_visitors/asm_instruction_finalizer.hpp"
#include "asm_gen/asm_node.hpp"

AsmInstructionFinalizer::AsmInstructionFinalizer(int size)
    : stack_size(size) {}

void AsmInstructionFinalizer::visit(AsmProgram* node) {
    if (node->func_ptr){
        node->func_ptr->accept(this);
    }
}

void AsmInstructionFinalizer::visit(AsmFunction* node) {
    //initializes the instructions vector in the private members
    instructions = &(node->instructions);

    //Makes a copy of raw pointers so that we could iterate over a copy 
    //and modify the original without issue
    std::vector<AsmInstruction*> saved_instructions;
    for (const auto& instr : *instructions) {
        saved_instructions.push_back(instr.get());
    }    

    auto stack_allocator = std::make_unique<StackAllocate>();
    stack_allocator->size = abs(stack_size);
    for (const auto &ptr : saved_instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    //Adds allocate stack instruction
    instructions->insert(instructions->begin(), std::move(stack_allocator));
}

//Determines if the mov instruction has both operands as stack locations
//If so, remove said mov instruction and then adds two new mov instructions using R10D as scratch reg
//Multiple scratch register are dynamically created since nodes are cleaned up recursively
void AsmInstructionFinalizer::visit(AsmMov* node) {
    auto src = std::dynamic_pointer_cast<StackLocation>(node->src);
    auto dst = std::dynamic_pointer_cast<StackLocation>(node->dst);
    if (src != nullptr && dst != nullptr){
        auto scratch = std::make_shared<AsmReg>();
        scratch->name = R10;

        auto mov_1 = std::make_unique<AsmMov>();
        mov_1->src = node->src;
        mov_1->dst = scratch;
    
        auto mov_2 = std::make_unique<AsmMov>();
        mov_2->src = scratch;
        mov_2->dst = node->dst;

        for (auto it = instructions->begin(); it != instructions->end(); ++it){
            if ((*it).get() == node){
                it = instructions->erase(it);
                it = instructions->insert(it, std::move(mov_2));
                it = instructions->insert(it, std::move(mov_1));
                break;
            }
        }
    }
}

//Add and sub instructions can't have memory addresses as both operands
//Multiplication can't have memory addresses as its dst operand
void AsmInstructionFinalizer::visit(AsmBinary* node) {
    auto src = std::dynamic_pointer_cast<StackLocation>(node->src);
    auto dst = std::dynamic_pointer_cast<StackLocation>(node->dst);
    if (node->op == Mult){
        //I may add constructors to the nodes, but I also want to keep their POD-likeness
        if (dst != nullptr){
            auto scratch = std::make_shared<AsmReg>();
            scratch->name = R11;
    
            auto mov_1 = std::make_unique<AsmMov>();
            mov_1->src = node->dst;
            mov_1->dst = scratch;

            node->dst = scratch;
        
            auto mov_2 = std::make_unique<AsmMov>();
            mov_2->src = scratch;
            mov_2->dst = mov_1->src;

            //Replaces instructions in the list
            for (auto it = instructions->begin(); it != instructions->end(); ++it){
                if ((*it).get() == node){
                    it = instructions->insert(it, std::move(mov_1));
                    it++;
                    it++;
                    instructions->insert(it, std::move(mov_2));
                    break;
                }
            }
        }
    }
    else if (node->op == Sub || node->op == Add){
        if (src != nullptr && dst != nullptr){
            auto scratch = std::make_shared<AsmReg>();
            scratch->name = R10;
            
            auto mov = std::make_unique<AsmMov>();
            mov->src = src;
            mov->dst = scratch;
            node->src = scratch;

            for (auto it = instructions->begin(); it != instructions->end(); ++it){
                if ((*it).get() == node){
                    instructions->insert(it, std::move(mov));
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
    auto operand = std::dynamic_pointer_cast<AsmImm>(node->operand_ptr);
    if (operand != nullptr){
        auto scratch = std::make_shared<AsmReg>();
        scratch->name = R10;

        auto mov = std::make_unique<AsmMov>();
        mov->src = node->operand_ptr;
        mov->dst = scratch;
        node->operand_ptr = scratch;

    for (auto it = instructions->begin(); it != instructions->end(); ++it){
        if ((*it).get() == node){
            instructions->insert(it, std::move(mov));
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