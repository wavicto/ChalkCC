#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <iostream>
#include "c_node.hpp"
#include "asm_node.hpp"

class Visitor {
    public:
    virtual void visit(program* node) = 0;
    virtual void visit(function* node) = 0;
    virtual void visit(statement* node) = 0;
    virtual void visit(expression* node) = 0;
    virtual void visit(constant* node) = 0;

    virtual void visit(asm_program* node) = 0;
    virtual void visit(asm_function* node) = 0;
    virtual void visit(asm_instruction* node) = 0;
    virtual void visit(asm_mov* node) = 0;
    virtual void visit(asm_ret* node) = 0;
    virtual void visit(asm_operand* node) = 0;
    virtual void visit(asm_reg* node) = 0;
    virtual void visit(asm_imm* node) = 0;
    virtual ~Visitor();
};

class Cleaner : public Visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;

    void visit(asm_program* node) override;
    void visit(asm_function* node) override;
    void visit(asm_instruction* node) override;
    void visit(asm_mov* node) override;
    void visit(asm_ret* node) override;
    void visit(asm_operand* node) override;
    void visit(asm_reg* node) override;
    void visit(asm_imm* node) override;
};

class Traveler : public Visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;

    void visit(asm_program* node) override;
    void visit(asm_function* node) override;
    void visit(asm_instruction* node) override;
    void visit(asm_mov* node) override;
    void visit(asm_ret* node) override;
    void visit(asm_operand* node) override;
    void visit(asm_reg* node) override;
    void visit(asm_imm* node) override;
};

class Generator : public Visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;
    
    asm_program* gen(program* node);
    asm_function* gen(function* node);
    asm_instruction* gen(statement* node);
    asm_instruction* gen(expression* node);

    void visit(asm_program* node) override;
    void visit(asm_function* node) override;
    void visit(asm_instruction* node) override;
    void visit(asm_mov* node) override;
    void visit(asm_ret* node) override;
    void visit(asm_operand* node) override;
    void visit(asm_reg* node) override;
    void visit(asm_imm* node) override;
};

#endif