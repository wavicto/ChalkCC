#ifndef ASM_NODE_HPP
#define ASM_NODE_HPP

#include <string>
#include <vector>
#include "asm_gen/asm_visitors/asm_visitor.hpp"

//Register names, size agnostic
enum Reg {
    AX,
    R10,
    DX,
    R11
};

enum UnaryOperator {
    Not,
    Neg
};

enum BinaryOperator {
    Add,
    Sub,
    Mult
};

class AsmNode {
    public:
    virtual void accept(AsmVisitor* v) = 0;
    virtual ~AsmNode();
};

class AsmProgram : public AsmNode {
    public:
    virtual void accept(AsmVisitor* v) override;
    AsmFunction* func_ptr;
};

class AsmFunction : public AsmNode {
    public:
    virtual void accept(AsmVisitor* v) override;
    std::string name;
    std::vector <AsmInstruction*> instructions;
};

class AsmInstruction : public AsmNode {
    public:
    virtual void accept(AsmVisitor* v) = 0;
};

class AsmMov : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;
    AsmOperand* src;
    AsmOperand* dst;
};

class AsmRet : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;
};

class AsmUnary : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;
    UnaryOperator op;
    AsmOperand* operand_ptr;
};

class AsmBinary : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;

    BinaryOperator op;
    AsmOperand* left_operand;
    AsmOperand* right_operand;
};

class Idiv : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;

    AsmOperand* operand_ptr;
};

class Cdq : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;

};

class StackAllocate : public AsmInstruction {
    public:
    virtual void accept(AsmVisitor* v) override;
    int size;
};

class AsmOperand : public AsmNode {
    public:
    virtual void accept(AsmVisitor* v) override = 0;
};

class AsmReg : public AsmOperand {
    public:
    virtual void accept(AsmVisitor* v) override;
    Reg name;
};

class AsmImm : public AsmOperand {
    public:
    virtual void accept(AsmVisitor* v) override;
    int value;
};

class AsmPseudoReg : public AsmOperand {
    public:
    virtual void accept(AsmVisitor* v) override;
    std::string id;
};

class StackLocation : public AsmOperand {
    public:
    virtual void accept(AsmVisitor* v) override;
    int rbp_offset;
};

#endif