#include "ir_gen/tac_visitors/tac_printer.hpp"
#include "ir_gen/tac_node.hpp"

void TacPrinter::visit(TacProgram* node) {
    std::cout << "Program:" << std::endl;
    if (node->func_ptr) {
        node->func_ptr->accept(this);
    }
}

void TacPrinter::visit(TacFunction* node) {
    std::cout << "Function: Name: " << node->id << std::endl;
    for (const auto& instr : node->body) {
        if (instr) {
            instr->accept(this);
        }
    }
}

void TacPrinter::visit(TacReturn* node) {
    std::cout << "Instruction: Return: ";
    if (node->val_ptr) {
        node->val_ptr->accept(this);
    }
}

void TacPrinter::visit(TacUnary* node) {
    std::cout << "Instruction: Unary: " << std::endl;

    std::cout << "\tOperator: ";
    switch (node->op) {
        case Complement: 
            std::cout << "Complement" << std::endl; 
            break;
        case Negation: 
            std::cout<< "Negation" << std::endl; 
            break;
        default: 
            std::cout << "Unknown Operator" << std::endl; 
            break;
    }

    std::cout << "\tSRC: ";
    if (node->src) {
        node->src->accept(this);
    }

    std::cout << "\tDST: ";
    if (node->dst) {
        node->dst->accept(this);
    }
}

void TacPrinter::visit(TacBinary* node) {
    std::cout << "Instruction: Binary: " << std::endl;

    std::cout << "\tOperator: ";
    switch (node->binary_op) {
        case Addition: 
            std::cout << "Addition" << std::endl; 
            break;
        case Negation: 
            std::cout<< "Subtraction" << std::endl; 
            break;
        case Multiplication: 
            std::cout<< "Multiplication" << std::endl; 
            break;
        case Division: 
            std::cout<< "Division" << std::endl; 
            break;
        default: 
            std::cout << "Unknown Operator" << std::endl; 
            break;
    }

    std::cout << "\tSRC_1: ";
    if (node->src_1) {
        node->src_1->accept(this);
    }

    std::cout << "\tSRC_2: ";
    if (node->src_2) {
        node->src_2->accept(this);
    }

    std::cout << "\tDST: ";
    if (node->dst) {
        node->dst->accept(this);
    }
}

void TacPrinter::visit(TacConstant* node) {
    std::cout << "Value: Constant(" << node->value << ")" << std::endl;
}

void TacPrinter::visit(TacVar* node) {
    std::cout << "Value: Variable(" << node->name << ")" << std::endl;
}