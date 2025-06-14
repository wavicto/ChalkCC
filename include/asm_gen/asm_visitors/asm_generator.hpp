#ifndef ASM_GENERATOR_HPP    
#define ASM_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Generates asm file through AsmAST traversal
class AsmGenerator : public AsmVisitor {
    public:
    virtual void visit(AsmProgram* node) override;
    virtual void visit(AsmFunction* node) override;
    virtual void visit(AsmMov* node) override;
    virtual void visit(AsmRet* node) override;
    virtual void visit(AsmUnary* node) override;
    virtual void visit(AsmBinary* node) override;
    virtual void visit(Cdq* node) override;
    virtual void visit(Idiv* node) override;
    virtual void visit(StackAllocate* node) override;
    virtual void visit(AsmReg* node) override;
    virtual void visit(AsmImm* node) override;
    virtual void visit(AsmPseudoReg* node) override;
    virtual void visit(StackLocation* node) override;
    
    std::ofstream file;
};

#endif