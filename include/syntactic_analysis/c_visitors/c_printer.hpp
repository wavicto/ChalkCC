#ifndef C_PRINTER_HPP
#define C_PRINTER_HPP

#include <iostream>
#include "syntactic_analysis/c_visitors//c_visitor.hpp"

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