#ifndef ASM_CLEANER_HPP    
#define ASM_CLEANER_HPP

#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Cleans up ASM AST nodes
class asm_cleaner : public asm_visitor {
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
};

#endif