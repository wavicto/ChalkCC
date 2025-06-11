#ifndef C_CLEANER_HPP
#define C_CLEANER_HPP

#include "syntactic_analysis/c_visitors/c_visitor.hpp"

//Cleans up C AST nodes
class c_cleaner : public c_visitor {
    public:
    void visit(program* node) override;
    void visit(function* node) override;
    void visit(statement* node) override;
    void visit(constant* node) override;
    void visit(unary_op* node) override;
};

#endif