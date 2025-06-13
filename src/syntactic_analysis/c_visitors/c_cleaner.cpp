#include "syntactic_analysis/c_visitors//c_cleaner.hpp"
#include "syntactic_analysis/c_node.hpp"

void CCleaner::visit(Program* node){
    Function* ptr = node->func_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void CCleaner::visit(Function* node){
    Statement* ptr = node->state_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void CCleaner::visit(Statement* node){
    Expression* ptr = node->exp_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void CCleaner::visit(UnaryOp* node) {
    Expression* ptr = node->exp_ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void CCleaner::visit(BinaryOp* node){
    if (node->exp_left){
        (node->exp_left)->accept(this);
    }
    if (node->exp_right){
        (node->exp_right)->accept(this);
    }
    delete node;
}

void CCleaner::visit(Constant* node){
    delete node;
}