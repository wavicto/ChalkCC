#ifndef C_VISITOR_HPP
#define C_VISITOR_HPP

#include "lexical_analysis/token.hpp"

//Forward declaration
class program;
class function;
class statement;
class constant;
class expression;
class unary_op;

//Abstract visitor interface
class c_visitor {
    public:
    virtual void visit(program* node) = 0;
    virtual void visit(function* node) = 0;
    virtual void visit(statement* node) = 0;
    virtual void visit(constant* node) = 0;
    virtual void visit(unary_op* node) = 0;
    virtual ~c_visitor(){}
};

#endif