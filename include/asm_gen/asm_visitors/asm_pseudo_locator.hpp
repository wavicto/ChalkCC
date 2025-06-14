#ifndef ASM_PSEUDO_LOCATOR_HPP    
#define ASM_PSEUDO_LOCATOR_HPP

#include <unordered_map>
#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Second compiler pass that asssigns memory location for pseudo registers
class AsmPseudoLocator: public AsmVisitor {
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

    AsmPseudoLocator(std::unordered_map<AsmPseudoReg*, int> &map);

    private:
    std::unordered_map<AsmPseudoReg*, int>& pseudo_map;
};

#endif