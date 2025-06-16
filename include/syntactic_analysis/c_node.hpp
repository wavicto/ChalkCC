#ifndef C_NODE_HPP    
#define C_NODE_HPP

#include <string>
#include <memory>
#include "syntactic_analysis/c_visitors/c_visitor.hpp"
#include "ir_gen/tac_node.hpp"
#include "ir_gen/tac_ast.hpp"

//Forward declaration
class TacAST;

class ASTNode {
    public:
    virtual void accept(CVisitor* v) = 0;
    virtual ~ASTNode();
};

class Program : public ASTNode {
    public:
    virtual void accept(CVisitor* v) override;

    std::unique_ptr<Function> func_ptr;
};

class Function : public ASTNode {
    public:
    virtual void accept(CVisitor* v) override;

    std::unique_ptr<Statement> state_ptr;
    std::string name;
};

class Statement: public ASTNode {
    public:
    virtual void accept(CVisitor* v) override;

    std::unique_ptr<Expression> exp_ptr;
};

class Expression: public ASTNode {
    public:
    virtual void accept(CVisitor* v) = 0;
    //Asists with TAC_AST generation through polymorphism
    virtual std::shared_ptr<TacVal> gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body) = 0;
};

class Constant : public Expression {
    public:
    virtual void accept(CVisitor* v) override;
    virtual std::shared_ptr<TacVal> gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body) override;

    int value;
};

class UnaryOp : public Expression {
    public:
    virtual void accept(CVisitor* v) override;
    virtual std::shared_ptr<TacVal> gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body) override;

    TokenType type;
    std::unique_ptr<Expression> exp_ptr;
};

class BinaryOp : public Expression {
    public:
    virtual void accept(CVisitor* v) override;
    virtual std::shared_ptr<TacVal> gen(TacAST* tree, std::vector<std::unique_ptr<TacInstruction>>& body) override;

    //Negation is interpreted the same as subtraction
    TokenType op;
    std::unique_ptr<Expression> exp_left;
    std::unique_ptr<Expression> exp_right;
};

#endif
