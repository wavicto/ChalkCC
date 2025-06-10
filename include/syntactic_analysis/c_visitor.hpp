#ifndef C_VISITOR_HPP
#define C_VISITOR_HPP

#include "lexical_analysis/token.hpp"

//forward declaration
class program;
class function;
class statement;
class constant;
class expression;
class unary_op;

class c_visitor {
    public:
    virtual void visit(program* node) = 0;
    virtual void visit(function* node) = 0;
    virtual void visit(statement* node) = 0;
    virtual void visit(constant* node) = 0;
    virtual void visit(unary_op* node) = 0;
    virtual ~c_visitor();
};

//Cleans up C AST nodes
class c_cleaner : public c_visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(constant* node) override;
    void visit(unary_op* node) override;
};

//Prints C AST structure
class c_printer : public c_visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(constant* node) override;
    void visit(unary_op* node) override;
};

#endif