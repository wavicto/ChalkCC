#include "ir_gen/tac_node.hpp"

TacNode::~TacNode(){}

void TacProgram::accept(TacVisitor* v) {
    v->visit(this);
}

void TacFunction::accept(TacVisitor* v) {
    v->visit(this);
}

void TacReturn::accept(TacVisitor* v) {
    v->visit(this);
}

void TacUnary::accept(TacVisitor* v) {
    v->visit(this);
}

void TacBinary::accept(TacVisitor* v) {
    v->visit(this);
}

void TacConstant::accept(TacVisitor* v) {
    v->visit(this);
}

void TacVar::accept(TacVisitor* v) {
    v->visit(this);
}

void TacReturn::gen(AsmAST* tree, std::vector <AsmInstruction*> &instructions){
    tree->gen(this, instructions);
}

void TacUnary::gen(AsmAST* tree, std::vector <AsmInstruction*> &instructions){
    tree->gen(this, instructions);
}

void TacBinary::gen(AsmAST* tree, std::vector <AsmInstruction*> &instructions){
    //placeholder for now
}

AsmOperand* TacConstant::gen(AsmAST* tree){
    return tree->gen(this);
}

AsmOperand* TacVar::gen(AsmAST* tree){
    return tree->gen(this);
}