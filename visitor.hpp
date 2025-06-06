#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <iostream>
#include <fstream>

//forward declaration
class program;
class function;
class statement;
class expression;
class constant;

class asm_program;
class asm_function;
class asm_instruction;
class asm_mov;
class asm_ret;
class asm_operand;
class asm_reg;
class asm_imm;

class c_visitor {
    public:
    virtual void visit(program* node) = 0;
    virtual void visit(function* node) = 0;
    virtual void visit(statement* node) = 0;
    virtual void visit(expression* node) = 0;
    virtual void visit(constant* node) = 0;
    virtual ~c_visitor();
};

//cleans up C AST nodes
class c_cleaner : public c_visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;
};

//prints C AST structure
class c_printer : public c_visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;
};

class asm_visitor {
    public:
    virtual void visit(asm_program* node) = 0;
    virtual void visit(asm_function* node) = 0;
    virtual void visit(asm_instruction* node) = 0;
    virtual void visit(asm_mov* node) = 0;
    virtual void visit(asm_ret* node) = 0;
    virtual void visit(asm_operand* node) = 0;
    virtual void visit(asm_reg* node) = 0;
    virtual void visit(asm_imm* node) = 0;
    virtual ~asm_visitor();
};

//cleans up ASM AST nodes
class asm_cleaner : public asm_visitor {
    public:
    void visit(asm_program* node) override;
    void visit(asm_function* node) override;
    void visit(asm_instruction* node) override;
    void visit(asm_mov* node) override;
    void visit(asm_ret* node) override;
    void visit(asm_operand* node) override;
    void visit(asm_reg* node) override;
    void visit(asm_imm* node) override;
};

//generates asm from AST
//objects have an asm file
class asm_generator : public asm_visitor {
    public:
    void visit(asm_program* node) override;
    void visit(asm_function* node) override;
    void visit(asm_instruction* node) override;
    void visit(asm_mov* node) override;
    void visit(asm_ret* node) override;
    void visit(asm_operand* node) override;
    void visit(asm_reg* node) override;
    void visit(asm_imm* node) override;

    std::ofstream file;
};

#endif