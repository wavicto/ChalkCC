#ifndef ASM_NODE_HPP
#define ASM_NODE_HPP

#include <string>
#include "asm_visitor.hpp"
#include <vector>

//register names, size agnostic
enum Reg {
    AX,
    R10
};

enum unary_operator {
    Not,
    Neg
};

class ASMNode {
    public:
    virtual void accept(asm_visitor* v) = 0;
    virtual ~ASMNode();
};

class asm_program : public ASMNode {
    public:
    virtual void accept(asm_visitor* v) override;
    asm_function* func_ptr;
};

class asm_function : public ASMNode {
    public:
    virtual void accept(asm_visitor* v) override;
    std::string name;
    std::vector <asm_instruction*> instructions;
};

class asm_instruction : public ASMNode {
    public:
    virtual void accept(asm_visitor* v) = 0;
};

class asm_mov : public asm_instruction {
    public:
    virtual void accept(asm_visitor* v) override;
    asm_operand* src;
    asm_operand* dst;
};

class asm_ret : public asm_instruction {
    public:
    virtual void accept(asm_visitor* v) override;
};

class asm_unary : public asm_instruction {
    public:
    virtual void accept(asm_visitor* v) override;
    unary_operator op;
    asm_operand* operand_ptr;
};

class allocate_stack : public asm_instruction {
    public:
    virtual void accept(asm_visitor* v) override;
    int bytes;
};

class asm_operand : public ASMNode {
    public:
    virtual void accept(asm_visitor* v) override = 0;
};

class asm_reg : public asm_operand {
    public:
    virtual void accept(asm_visitor* v) override;
    Reg name;
};

class asm_imm : public asm_operand {
    public:
    virtual void accept(asm_visitor* v) override;
    int value;
};

class asm_pseudo_reg : public asm_operand {
    public:
    virtual void accept(asm_visitor* v) override;
    std::string id;
};

class stack_location : public asm_operand {
    public:
    virtual void accept(asm_visitor* v) override;
    int rbp_offset;
};

#endif