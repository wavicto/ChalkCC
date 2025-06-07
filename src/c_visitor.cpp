#include "c_visitor.hpp"
#include "c_node.hpp"

c_visitor::~c_visitor() {}

void c_cleaner::visit(program* node){
    function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void c_cleaner::visit(function* node){
    statement* ptr = node->state_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void c_cleaner::visit(statement* node){
    expression* ptr = node->exp_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void c_cleaner::visit(unary_op* node) {
    expression* ptr = node->exp_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void c_cleaner::visit(constant* node){
    delete node;
}

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