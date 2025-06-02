#ifndef C_NODE_HPP    
#define C_NODE_HPP

#include <string>
#include "visitor.hpp"

class program;
class function;
class statement;
class expression;
class constant;

class ASTNode {
    public:
    virtual void accept(Visitor* v) = 0;
    virtual ~ASTNode(){}
};

class program : public ASTNode {
    public:
    virtual void accept(Visitor* v) override;
    function* ptr;
};

class function : public ASTNode {
    public:
    virtual void accept(Visitor* v) override;

    statement* ptr;
    std::string name;
};

class statement: public ASTNode {
    public:
    virtual void accept(Visitor* v) override;

    expression* ptr;
};

class expression: public ASTNode {
    public:
    virtual void accept(Visitor* v) override;

    constant* ptr;
};

class constant : public expression {
    public:
    virtual void accept(Visitor* v) override;

    int value;
};


#endif