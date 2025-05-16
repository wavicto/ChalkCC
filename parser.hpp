#ifndef PARSER_HPP    
#define PARSER_HPP

#include "lexer.hpp"

class AST {
    public:

    AST(std::vector<Token> tokens);

    ~AST();

    private:
    program* root;
};


class Visitor {
    public:
    virtual void visit(program* node) = 0;
    virtual void visit(function* node) = 0;
    virtual void visit(statement* node) = 0;
    virtual void visit(expression* node) = 0;
    virtual void visit(constant* node) = 0;
    virtual void visit(return_statement* node) = 0;
    virtual ~Visitor();
};

class Cleaner : public Visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(expression* node) override;
    void visit(constant* node) override;
    void visit(return_statement* node) override;
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

    return_statement* ptr;
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

class return_statement: public statement {
    public:
    virtual void accept(Visitor* v) override;

    expression* ptr;
};

#endif