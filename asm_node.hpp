#ifndef ASM_NODE_HPP
#define ASM_NODE_HPP

#include <string>
#include "asm_visitor.hpp"
#include <vector>

enum Reg {
    EAX
};

class ASMNode {
    public:
    virtual void accept(asm_visitor* v) = 0;
    virtual ~ASMNode(){}
};

class asm_program : public ASMNode {
    public:
    virtual void accept(asm_visitor* v) override;
    asm_function* ptr;
};

class asm_function : public asm_program {
    public:
    virtual void accept(asm_visitor* v) override;
    std::string name;
    std::vector <asm_instruction*> instructions;
};

class asm_instruction : public asm_function {
    public:
    virtual void accept(asm_visitor* v) override;
    asm_instruction* ptr;
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

class asm_operand : public asm_program {
    public:
    virtual void accept(asm_visitor* v) override;
    asm_operand* ptr;
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

#endif