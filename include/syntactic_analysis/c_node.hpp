#ifndef C_NODE_HPP    
#define C_NODE_HPP

#include <string>
#include <iostream>
#include "syntactic_analysis/c_visitor.hpp"
#include "ir_gen/tac_node.hpp"
#include "ir_gen/tac_ast.hpp"

//Forward declaration
class TAC_AST;

class ASTNode {
    public:
    virtual void accept(c_visitor* v) = 0;
    virtual ~ASTNode();
};

class program : public ASTNode {
    public:
    virtual void accept(c_visitor* v) override;

    function* func_ptr;
};

class function : public ASTNode {
    public:
    virtual void accept(c_visitor* v) override;

    statement* state_ptr;
    std::string name;
};

class statement: public ASTNode {
    public:
    virtual void accept(c_visitor* v) override;

    expression* exp_ptr;
};

class expression: public ASTNode {
    public:
    virtual void accept(c_visitor* v) = 0;
    //Asists with tac IR generation through polymorphism
    virtual tac_val* gen(TAC_AST* tree, std::vector<tac_instruction*>& body) = 0;
};

class constant : public expression {
    public:
    virtual void accept(c_visitor* v) override;
    virtual tac_val* gen(TAC_AST* tree, std::vector<tac_instruction*>& body) override;

    int value;
};

class unary_op : public expression {
    public:
    virtual void accept(c_visitor* v) override;
    virtual tac_val* gen(TAC_AST* tree, std::vector<tac_instruction*>& body) override;

    TokenType type;
    expression* exp_ptr;
};

#endif