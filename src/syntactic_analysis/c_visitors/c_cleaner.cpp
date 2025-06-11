#include "syntactic_analysis/c_visitors//c_cleaner.hpp"
#include "syntactic_analysis/c_node.hpp"

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