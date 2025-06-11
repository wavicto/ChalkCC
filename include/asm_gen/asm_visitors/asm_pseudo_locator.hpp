#ifndef ASM_PSEUDO_LOCATOR_HPP    
#define ASM_PSEUDO_LOCATOR_HPP

#include <unordered_map>
#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Compiler pass that asssigns memory location for pseudo registers
class asm_pseudo_locator: public asm_visitor {
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

    asm_pseudo_locator(std::unordered_map<asm_pseudo_reg*, int> &map);

    private:
    std::unordered_map<asm_pseudo_reg*, int>& pseudo_map;
};

#endif