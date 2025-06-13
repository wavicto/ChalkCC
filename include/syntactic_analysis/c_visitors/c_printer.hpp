#ifndef C_PRINTER_HPP
#define C_PRINTER_HPP

#include <iostream>
#include "syntactic_analysis/c_visitors//c_visitor.hpp"

//Prints C AST structure
class CPrinter : public CVisitor {
    public:
    void visit(Program* node) override;
    void visit(Function* node) override;
    void visit(Statement* node) override;
    void visit(Constant* node) override;
    void visit(UnaryOp* node) override;
    void visit(BinaryOp* node) override;
};

#endif