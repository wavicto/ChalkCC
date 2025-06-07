#include "c_node.hpp"

ASTNode::~ASTNode(){}

void program::accept(c_visitor* v){
    v->visit(this);
}

void function::accept(c_visitor* v){
    v->visit(this);
}

void statement::accept(c_visitor* v){
    v->visit(this);
}

void unary_op::accept(c_visitor* v){
    v->visit(this);
}

void constant::accept(c_visitor* v){
    v->visit(this);
}