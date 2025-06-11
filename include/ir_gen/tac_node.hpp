#ifndef TAC_NODE_HPP    
#define TAC_NODE_HPP

#include <string>
#include <vector>
#include "lexical_analysis/token.hpp"
#include "ir_gen/tac_visitors/tac_visitor.hpp"
#include "asm_gen/asm_node.hpp"
#include "asm_gen/codegen.hpp"

//Forward declaration
class AsmAST;

class TacNode {
    public:
    virtual void accept(TacVisitor* v) = 0;
    virtual ~TacNode();
};

class TacProgram : public TacNode {
    public:
    virtual void accept(TacVisitor* v) override;

    TacFunction* func_ptr;
};

class TacFunction : public TacNode {
    public:
    virtual void accept(TacVisitor* v) override;

    std::string id;
    std::vector<TacInstruction*> body;
};

class TacInstruction : public TacNode {
    public:
    virtual void accept(TacVisitor* v) = 0;
    //Asists AsmAST generation through polymorphism on children classes
    virtual void gen(AsmAST* tree, std::vector <AsmInstruction*> &instructions) = 0;
};

class TacReturn : public TacInstruction {
    public:
    virtual void accept(TacVisitor* v) override;
    virtual void gen(AsmAST* tree, std::vector <AsmInstruction*> &instructions) override;

    TacVal* val_ptr;
};

class TacUnary : public TacInstruction{
    public:
    virtual void accept(TacVisitor* v) override;
    virtual void gen(AsmAST* tree, std::vector <AsmInstruction*> &instructions) override;

    TokenType op;
    TacVal* src;
    //dst must be a var
    TacVal* dst;
};

class TacVal : public TacNode {
    public:
    virtual void accept(TacVisitor* v) = 0;
    //Asists AsmAST generation through polymorphism on children classes
    virtual AsmOperand* gen(AsmAST* tree) = 0;
};

class TacConstant : public TacVal {
    public:
    virtual void accept(TacVisitor* v) override;
    virtual AsmOperand* gen(AsmAST* tree) override;

    int value;
};

class TacVar : public TacVal {
    public:
    virtual void accept(TacVisitor* v) override;
    virtual AsmOperand* gen(AsmAST* tree) override;

    std::string name;
};

#endif