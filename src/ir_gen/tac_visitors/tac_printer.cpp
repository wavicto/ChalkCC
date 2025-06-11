#include "ir_gen/tac_visitors/tac_printer.hpp"
#include "ir_gen/tac_node.hpp"

void TacPrinter::visit(TacProgram* node) {
    std::cout << "Program:" << std::endl;
    TacFunction* ptr = node->func_ptr;
    if (ptr) {
        ptr->accept(this);
    }
}

void TacPrinter::visit(TacFunction* node) {
    std::cout << "Function: Name: " << node->id << std::endl;
    for (TacInstruction* instr : node->body) {
        if (instr) {
            instr->accept(this);
        }
    }
}

void TacPrinter::visit(TacReturn* node) {
    std::cout << "Instruction: Return: ";
    TacVal* ptr = node->val_ptr;
    if (ptr) {
        ptr->accept(this);
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
            std::cout << "Error" << std::endl; 
            break;
    }

    std::cout << "\tSRC: ";
    TacVal* src = node->src;
    if (src) {
        src->accept(this);
    }

    std::cout << "\tDST: ";
    TacVal* dst = node->dst;
    if (dst) {
        dst->accept(this);
    }
}

void TacPrinter::visit(TacConstant* node) {
    std::cout << "Value: Constant(" << node->value << ")" << std::endl;
}

void TacPrinter::visit(TacVar* node) {
    std::cout << "Value: Variable(" << node->name << ")" << std::endl;
}