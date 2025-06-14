#ifndef ASM_INSTRUCTION_FINALIZER_HPP    
#define ASM_INSTRUCTION_FINALIZER_HPP

#include <vector>
#include <stdexcept>
#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Class for third compiler pass
//Allocates stack size
//Fixes mov instructions that have both operands as stack locations using R10D as a scratch register
class AsmInstructionFinalizer: public AsmVisitor {
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

    AsmInstructionFinalizer(int size);

    private:
    int stack_size;
    std::vector <AsmInstruction*> *instructions;
};

#endif