#include "syntactic_analysis/c_node.hpp"

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

tac_val* constant::gen(TAC_AST* tree, std::vector<tac_instruction*>& body){
    return tree->gen(this);
}

tac_val* unary_op::gen(TAC_AST* tree, std::vector<tac_instruction*>& body){
    return tree->gen(this, body);
}
