#ifndef TAC_NODE_HPP    
#define TAC_NODE_HPP

#include <string>
#include <vector>
#include <memory>
#include "lexical_analysis/token.hpp"
#include "ir_gen/tac_visitors/tac_visitor.hpp"
#include "asm_gen/asm_node.hpp"
#include "asm_gen/codegen.hpp"

// Forward declaration
class AsmAST;

class TacNode {
public:
    virtual void accept(TacVisitor* v) = 0;
    virtual ~TacNode();
};

class TacProgram : public TacNode {
public:
    virtual void accept(TacVisitor* v) override;

    std::unique_ptr<TacFunction> func_ptr;
};

class TacFunction : public TacNode {
public:
    virtual void accept(TacVisitor* v) override;

    std::string id;
    std::vector<std::unique_ptr<TacInstruction>> body;
};

class TacInstruction : public TacNode {
public:
    virtual void accept(TacVisitor* v) = 0;
    // Assists AsmAST generation through polymorphism on children classes
    virtual void gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions) = 0;
};

class TacReturn : public TacInstruction {
public:
    virtual void accept(TacVisitor* v) override;
    virtual void gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions) override;

    std::shared_ptr<TacVal> val_ptr;
};

class TacUnary : public TacInstruction {
public:
    virtual void accept(TacVisitor* v) override;
    virtual void gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions) override;

    TokenType op;
    std::shared_ptr<TacVal> src;
    std::shared_ptr<TacVal> dst;
};

class TacBinary : public TacInstruction {
public:
    virtual void accept(TacVisitor* v) override;
    virtual void gen(AsmAST* tree, std::vector<std::unique_ptr<AsmInstruction>> &instructions) override;

    TokenType binary_op;
    std::shared_ptr<TacVal> src_1;
    std::shared_ptr<TacVal> src_2;
    std::shared_ptr<TacVal> dst;
};

class TacVal : public TacNode {
public:
    virtual void accept(TacVisitor* v) = 0;
    // Assists AsmAST generation through polymorphism on children classes
    virtual std::shared_ptr<AsmOperand> gen(AsmAST* tree) = 0;
};

class TacConstant : public TacVal {
public:
    virtual void accept(TacVisitor* v) override;
    virtual std::shared_ptr<AsmOperand> gen(AsmAST* tree) override;

    int value;
};

class TacVar : public TacVal {
public:
    virtual void accept(TacVisitor* v) override;
    virtual std::shared_ptr<AsmOperand> gen(AsmAST* tree) override;

    std::string name;
};

#endif
