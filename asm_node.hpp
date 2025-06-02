#ifndef ASM_NODE_HPP
#define ASM_NODE_HPP

#include <string>
#include "visitor.hpp"
#include <vector>

class asm_program;
class asm_function;
class asm_instruction;
class asm_mov;
class asm_ret;
class asm_operand;
class asm_reg;
class asm_imm;

enum Reg {
    EAX
};

class ASMNode {
    public:
    virtual void accept(Visitor* v) = 0;
    virtual ~ASMNode(){}
};

class asm_program : ASMNode {
    public:
    virtual void accept(Visitor* v) override;
    asm_function* ptr;
};

class asm_function : asm_program {
    public:
    virtual void accept(Visitor* v) override;
    std::string name;
    std::vector <asm_instruction*> instructions;
};

class asm_instruction : asm_function {
    public:
    virtual void accept(Visitor* v) override;
    asm_instruction* ptr;
};

class asm_mov : asm_instruction {
    public:
    virtual void accept(Visitor* v) override;
    asm_operand* src;
    asm_operand* dst;
};

class asm_ret : asm_instruction {
    public:
    virtual void accept(Visitor* v) override;
};

class asm_operand : asm_program {
    public:
    virtual void accept(Visitor* v) override;
    asm_operand* ptr;
};

class asm_reg : asm_operand {
    public:
    virtual void accept(Visitor* v) override;
    Reg name;
};

class asm_imm : asm_operand {
    public:
    virtual void accept(Visitor* v) override;
    int value;
};

#endif