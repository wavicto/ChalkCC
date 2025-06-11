#include "asm_gen/asm_visitors/asm_printer.hpp"
#include "asm_gen/asm_node.hpp"

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