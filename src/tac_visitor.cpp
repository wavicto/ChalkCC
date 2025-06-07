#include "tac_visitor.hpp"
#include "tac_node.hpp"

tac_visitor::~tac_visitor(){}

void tac_cleaner::visit(tac_program* node){
    tac_function* ptr = node->func_ptr;
    if(ptr){
        ptr->accept(this);
    }
    delete node;
}

void tac_cleaner::visit(tac_function* node){
    for (auto ptr : node->body){
        if (ptr){
            ptr->accept(this);
        }
    }
    delete node;
}

void tac_cleaner::visit(tac_return* node){
    delete node;
}

void tac_cleaner::visit(tac_unary* node){
    tac_val* src = node->src;
    tac_val* dst = node->dst;

    if (src){
        src->accept(this);
    }
    if (dst ){
        dst->accept(this);
    }
    delete node;
}

void tac_cleaner::visit(tac_constant* node){
    delete node;
}

//Temp vars will be cleaned up all together in a private method in TAC_AST
void tac_cleaner::visit(tac_var* node){}

void tac_printer::visit(tac_program* node) {
    std::cout << "Program:" << std::endl;
    tac_function* ptr = node->func_ptr;
    if (ptr) {
        ptr->accept(this);
    }
}

void tac_printer::visit(tac_function* node) {
    std::cout << "Function: Name: " << node->id << std::endl;
    for (tac_instruction* instr : node->body) {
        if (instr) {
            instr->accept(this);
        }
    }
}

void tac_printer::visit(tac_return* node) {
    std::cout << "Instruction: Return: ";
    tac_val* ptr = node->val_ptr;
    if (ptr) {
        ptr->accept(this);
    }
}

void tac_printer::visit(tac_unary* node) {
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
    tac_val* src = node->src;
    if (src) {
        src->accept(this);
    }

    std::cout << "\tDST: ";
    tac_val* dst = node->dst;
    if (dst) {
        dst->accept(this);
    }
}

void tac_printer::visit(tac_constant* node) {
    std::cout << "Value: Constant(" << node->value << ")" << std::endl;
}

void tac_printer::visit(tac_var* node) {
    std::cout << "Value: Variable(" << node->name << ")" << std::endl;
}