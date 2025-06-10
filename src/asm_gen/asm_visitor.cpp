#include "asm_gen/asm_node.hpp"
#include "asm_gen/asm_visitor.hpp"

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

void asm_cleaner::visit(asm_unary* node){
    asm_operand* op_ptr = node->operand_ptr;
    if (op_ptr){
        op_ptr->accept(this);
    }
    delete node;
}

void asm_cleaner::visit(asm_ret* node){delete node;}
void asm_cleaner::visit(allocate_stack* node){delete node;}
void asm_cleaner::visit(asm_pseudo_reg* node){delete node;}
void asm_cleaner::visit(stack_location* node){delete node;}
void asm_cleaner::visit(asm_reg* node){delete node;}
void asm_cleaner::visit(asm_imm* node){delete node;}

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
    instructions->insert(instructions->begin(), stack_allocator);
}

void asm_instruction_finalizer::visit(asm_mov* node) {
    auto src = dynamic_cast<stack_location*>(node->src);
    auto dst = dynamic_cast<stack_location*>(node->dst);

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


void asm_generator::visit(asm_program* node){
    file.open("assembly.s");
    asm_function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    file << ".section .note.GNU-stack,\"\",@progbits" << std::endl;
}

void asm_generator::visit(asm_function* node){
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

void asm_generator::visit(asm_mov* node){
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

void asm_generator::visit(asm_unary* node){
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

void asm_generator::visit(allocate_stack* node){
    file << "\tsubq\t$" << node->size << ", %rsp" << std::endl;
}

void asm_generator::visit(asm_ret* node){
    file << "\tmovq\t%rbp, %rsp" << std::endl;
    file << "\tpopq\t%rbp" << std::endl;
    file << "\tret ";
}

void asm_generator::visit(asm_reg* node){
    switch(node->name){
        case 0:
            file << "%eax";
            break;
        case 1: 
            file << "%r10d";
    }
}

void asm_generator::visit(stack_location* node){
    file << node->rbp_offset << "(%rbp)";
}

void asm_generator::visit(asm_imm* node){
    file << "$" << node->value;
}

void asm_generator::visit(asm_pseudo_reg* node){}

void asm_printer::visit(asm_program* node) {
    std::cout << "Program:" << std::endl;
    asm_function* ptr = node->func_ptr;
    if (ptr) {
        ptr->accept(this);
    }
}

void asm_printer::visit(asm_function* node) {
    std::cout << "Function: Name: " << node->name << std::endl;
    for (asm_instruction* instr : node->instructions) {
        if (instr) {
            instr->accept(this);
        }
    }
}

void asm_printer::visit(asm_mov* node) {
    std::cout << "Instruction: Mov:" << std::endl;

    std::cout << "\tSRC: ";
    if (node->src) {
        node->src->accept(this);
    }

    std::cout << "\tDST: ";
    if (node->dst) {
        node->dst->accept(this);
    }
}

void asm_printer::visit(asm_ret* node) {
    std::cout << "Instruction: Ret" << std::endl;
}

void asm_printer::visit(asm_unary* node) {
    std::cout << "Instruction: Unary:" << std::endl;

    std::cout << "\tOperator: ";
    switch (node->op) {
        case Neg:
            std::cout << "NEG" << std::endl;
            break;
        case Not:
            std::cout << "NOT" << std::endl;
            break;
        default:
            std::cout << "UNKNOWN" << std::endl;
            break;
    }

    std::cout << "\tOperand: ";
    if (node->operand_ptr) {
        node->operand_ptr->accept(this);
    }
}

void asm_printer::visit(allocate_stack* node) {
    std::cout << "Instruction: Allocate Stack: " << node->size << " bytes" << std::endl;
}

void asm_printer::visit(asm_reg* node) {
    std::cout << "Operand: Register: ";
    switch (node->name) {
        case AX: std::cout << "RAX"; break;
        case R10: std::cout << "R10D"; break;
        default: std::cout << "UNKNOWN"; break;
    }
    std::cout << std::endl;
}

void asm_printer::visit(asm_imm* node) {
    std::cout << "Operand: Imm: " << node->value << std::endl;
}

void asm_printer::visit(asm_pseudo_reg* node) {
    std::cout << "Operand: Pseudo Register: " << node->id << std::endl;
}

void asm_printer::visit(stack_location* node) {
    std::cout << "Operand: Stack Location: " << node->rbp_offset << "(%rbp)" << std::endl;
}