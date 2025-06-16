#include "syntactic_analysis/c_node.hpp"

ASTNode::~ASTNode(){}

void Program::accept(CVisitor* v){
    v->visit(this);
}

void Function::accept(CVisitor* v){
    v->visit(this);
}

void Statement::accept(CVisitor* v){
    v->visit(this);
}

void UnaryOp::accept(CVisitor* v){
    v->visit(this);
}

void BinaryOp::accept(CVisitor* v){
    v->visit(this);
}

void Constant::accept(CVisitor* v){
    v->visit(this);
}

TacVal* Constant::gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body){
    return tree->gen(this);
}

TacVal* UnaryOp::gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body){
    return tree->gen(this, body);
}

TacVal* BinaryOp::gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body){
    return tree->gen(this, body);
}

