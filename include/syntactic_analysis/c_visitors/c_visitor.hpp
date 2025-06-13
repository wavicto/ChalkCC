#ifndef C_VISITOR_HPP
#define C_VISITOR_HPP

#include "lexical_analysis/token.hpp"

//Forward declaration
class Program;
class Function;
class Statement;
class Expression;
class Constant;
class UnaryOp;
class BinaryOp;

//Abstract visitor interface
class CVisitor {
    public:
    virtual void visit(Program* node) = 0;
    virtual void visit(Function* node) = 0;
    virtual void visit(Statement* node) = 0;
    virtual void visit(Constant* node) = 0;
    virtual void visit(UnaryOp* node) = 0;
    virtual void visit(BinaryOp* node) = 0;
    virtual ~CVisitor(){}
};

#endif