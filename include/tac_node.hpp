#include <string>
#include "visitor.hpp"
#include <vector>

/*
class TACNode {
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
*/