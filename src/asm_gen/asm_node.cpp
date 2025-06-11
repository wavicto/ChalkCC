#include "asm_gen/asm_node.hpp"

AsmNode::~AsmNode(){}

void AsmProgram::accept(AsmVisitor* v){
    v->visit(this);
}

void AsmFunction::accept(AsmVisitor* v){
    v->visit(this);
}

void AsmMov::accept(AsmVisitor* v){
    v->visit(this);
}

void StackAllocate::accept(AsmVisitor* v){
    v->visit(this);
}

void AsmPseudoReg::accept(AsmVisitor* v){
    v->visit(this);
}

void StackLocation::accept(AsmVisitor* v){
    v->visit(this);
}

void AsmUnary::accept(AsmVisitor* v){
    v->visit(this);
}
void AsmRet::accept(AsmVisitor* v){
    v->visit(this);
}

void AsmReg::accept(AsmVisitor* v){
    v->visit(this);
}

void AsmImm::accept(AsmVisitor* v){
    v->visit(this);
}