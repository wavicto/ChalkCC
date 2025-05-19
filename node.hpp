#ifndef NODE_HPP    
#define NODE_HPP

#include <string>
#include <iostream>

class program;
class function;
class statement;
class expression;
class constant;

class Visitor {
    public:
    virtual void visit(program* node) = 0;
    virtual void visit(function* node) = 0;
    virtual void visit(statement* node) = 0;
    virtual void visit(expression* node) = 0;
    virtual void visit(constant* node) = 0;
    virtual ~Visitor();
};

class Cleaner : public Visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;
};

class Traveler : public Visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;
};

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