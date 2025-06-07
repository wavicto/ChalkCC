#ifndef C_NODE_HPP    
#define C_NODE_HPP

#include <string>
#include <iostream>
#include "c_visitor.hpp"

class ASTNode {
    public:
    virtual void accept(c_visitor* v) = 0;
    virtual ~ASTNode(){}
};

class program : public ASTNode {
    public:
    virtual void accept(c_visitor* v) override;

    function* ptr;
};

class function : public ASTNode {
    public:
    virtual void accept(c_visitor* v) override;

    statement* ptr;
    std::string name;
};

class statement: public ASTNode {
    public:
    virtual void accept(c_visitor* v) override;

    expression* ptr;
};

class expression: public ASTNode {
    public:
    void accept(c_visitor* v) = 0;
};

class constant : public expression {
    public:
    virtual void accept(c_visitor* v) override;

    int value;
};

class unary_op : public expression {
    public:
    virtual void accept(c_visitor* v) override;

    TokenType type;
    expression* exp_ptr;
};


#endif