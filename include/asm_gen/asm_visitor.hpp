#ifndef ASM_VISITOR_HPP    
#define ASM_VISITOR_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

//forward declaration
class asm_program;
class asm_function;
class asm_mov;
class asm_ret;
class asm_unary;
class asm_instruction;
class asm_operand;
class allocate_stack;
class asm_reg;
class asm_imm;
class asm_pseudo_reg;
class stack_location;

class asm_visitor {
    public:
    virtual void visit(asm_program* node) = 0;
    virtual void visit(asm_function* node) = 0;
    virtual void visit(asm_mov* node) = 0;
    virtual void visit(asm_ret* node) = 0;
    virtual void visit(asm_unary* node) = 0;
    virtual void visit(allocate_stack* node) = 0;
    virtual void visit(asm_reg* node) = 0;
    virtual void visit(asm_imm* node) = 0;
    virtual void visit(asm_pseudo_reg* node) = 0;
    virtual void visit(stack_location* node) = 0;
    virtual ~asm_visitor();
};

//cleans up ASM AST nodes
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

//compiler pass that asssigns memory location for pseudo registers
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

//allocates stack size
//fixes mov instructions that have both operands as stack locations using R10D as a scratch register
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

//Generates asm file through ASM_AST traversal
class asm_generator : public asm_visitor {
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
    
    std::ofstream file;
};

//Prints ASM_AST structure
class asm_printer : public asm_visitor {
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