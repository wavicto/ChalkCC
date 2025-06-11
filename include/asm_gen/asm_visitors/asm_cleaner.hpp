#ifndef ASM_CLEANER_HPP    
#define ASM_CLEANER_HPP

#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Cleans up AsmAST nodes
class AsmCleaner : public AsmVisitor {
    public:
    virtual void visit(AsmProgram* node) override;
    virtual void visit(AsmFunction* node) override;
    virtual void visit(AsmMov* node) override;
    virtual void visit(AsmRet* node) override;
    virtual void visit(AsmUnary* node) override;
    virtual void visit(StackAllocate* node) override;
    virtual void visit(AsmReg* node) override;
    virtual void visit(AsmImm* node) override;
    virtual void visit(AsmPseudoReg* node) override;
    virtual void visit(StackLocation* node) override;
};

#endif