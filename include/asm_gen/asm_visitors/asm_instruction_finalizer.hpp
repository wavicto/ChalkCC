#ifndef ASM_INSTRUCTION_FINALIZER_HPP    
#define ASM_INSTRUCTION_FINALIZER_HPP

#include <vector>
#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Class for third compiler pass
//Allocates stack size
//Fixes mov instructions that have both operands as stack locations using R10D as a scratch register
class asm_instruction_finalizer: public asm_visitor {
    public:
    virtual void visit(asm_program* node) override;
    virtual void visit(asm_function* node) override;
    virtual void visit(asm_mov* node) override;
    virtual void visit(asm_ret* node) override;
    virtual void visit(asm_unary* node) override;
    virtual void visit(allocate_stack* node) override;
    virtual void visit(asm_reg* node) override;
    virtual void visit(asm_imm* node) override;
    virtual void visit(asm_pseudo_reg* node) override;
    virtual void visit(stack_location* node) override;

    asm_instruction_finalizer(int size);

    private:
    int stack_size;
    std::vector <asm_instruction*> *instructions;
};

#endif