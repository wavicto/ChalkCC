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

void TacReturn::gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions){
    tree->gen(this, instructions);
}

void TacUnary::gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions){
    tree->gen(this, instructions);
}

void TacBinary::gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions){
    tree->gen(this, instructions);
}

std::shared_ptr<AsmOperand> TacConstant::gen(AsmAST* tree){
    return tree->gen(this);
}

std::shared_ptr<AsmOperand> TacVar::gen(AsmAST* tree){
    return tree->gen(this);
}