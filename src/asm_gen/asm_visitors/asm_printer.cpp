#include "asm_gen/asm_visitors/asm_printer.hpp"
#include "asm_gen/asm_node.hpp"

void AsmPrinter::visit(AsmProgram* node) {
    std::cout << "Program:" << std::endl;
    AsmFunction* ptr = node->func_ptr;
    if (ptr) {
        ptr->accept(this);
    }
}

void AsmPrinter::visit(AsmFunction* node) {
    std::cout << "Function: Name: " << node->name << std::endl;
    for (AsmInstruction* instr : node->instructions) {
        if (instr) {
            instr->accept(this);
        }
    }
}

void AsmPrinter::visit(AsmMov* node) {
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

void AsmPrinter::visit(AsmRet* node) {
    std::cout << "Instruction: Ret" << std::endl;
}

void AsmPrinter::visit(AsmUnary* node) {
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

void AsmPrinter::visit(StackAllocate* node) {
    std::cout << "Instruction: Allocate Stack: " << node->size << " bytes" << std::endl;
}

void AsmPrinter::visit(AsmReg* node) {
    std::cout << "Operand: Register: ";
    switch (node->name) {
        case AX: std::cout << "RAX"; break;
        case R10: std::cout << "R10D"; break;
        default: std::cout << "UNKNOWN"; break;
    }
    std::cout << std::endl;
}

void AsmPrinter::visit(AsmImm* node) {
    std::cout << "Operand: Imm: " << node->value << std::endl;
}

void AsmPrinter::visit(AsmPseudoReg* node) {
    std::cout << "Operand: Pseudo Register: " << node->id << std::endl;
}

void AsmPrinter::visit(StackLocation* node) {
    std::cout << "Operand: Stack Location: " << node->rbp_offset << "(%rbp)" << std::endl;
}