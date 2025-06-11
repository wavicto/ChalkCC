#include "syntactic_analysis/c_visitors//c_printer.hpp"
#include "syntactic_analysis/c_node.hpp"

void c_printer::visit(program* node){
    std::cout << "Program: " << std::endl;
    function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void c_printer::visit(function* node){
    std::cout << "Function: Name: " << node->name << std::endl;
    statement* ptr = node->state_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void c_printer::visit(statement* node){
    std::cout << "Statement: Return " << std::endl;
    expression* ptr = node->exp_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void c_printer::visit(unary_op* node){
    Token t(node->type);
    std::cout << "Expression: Unary: " << t.get_type_name(t.get_type()) << std::endl;
    expression* ptr = node->exp_ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void c_printer::visit(constant* node){
    std::cout << "Expression: Constant(" << node->value << ")" << std::endl;
}