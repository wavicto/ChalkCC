#ifndef ASM_VISITOR_HPP    
#define ASM_VISITOR_HPP

#include <iostream>
#include <fstream>

//forward declaration
class asm_program;
class asm_function;
class asm_mov;
class asm_ret;
class asm_unary;
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
};

//generates asm from AST
//objects have an asm file
class asm_generator : public asm_visitor {
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

    std::ofstream file;
};

#endif