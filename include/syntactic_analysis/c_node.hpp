#ifndef C_NODE_HPP    
#define C_NODE_HPP

#include <string>
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

    Function* func_ptr;
};

class Function : public ASTNode {
    public:
    virtual void accept(CVisitor* v) override;

    Statement* state_ptr;
    std::string name;
};

class Statement: public ASTNode {
    public:
    virtual void accept(CVisitor* v) override;

    Expression* exp_ptr;
};

class Expression: public ASTNode {
    public:
    virtual void accept(CVisitor* v) = 0;
    //Asists with TAC_AST generation through polymorphism
    virtual TacVal* gen(TacAST* tree, std::vector<TacInstruction*>& body) = 0;
};

class Constant : public Expression {
    public:
    virtual void accept(CVisitor* v) override;
    virtual TacVal* gen(TacAST* tree, std::vector<TacInstruction*>& body) override;

    int value;
};

class UnaryOp : public Expression {
    public:
    virtual void accept(CVisitor* v) override;
    virtual TacVal* gen(TacAST* tree, std::vector<TacInstruction*>& body) override;

    TokenType type;
    Expression* exp_ptr;
};

#endif