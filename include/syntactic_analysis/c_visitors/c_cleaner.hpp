#ifndef C_CLEANER_HPP
#define C_CLEANER_HPP

#include "syntactic_analysis/c_visitors/c_visitor.hpp"

//Cleans up C AST nodes
class CCleaner : public CVisitor {
    public:
    void visit(Program* node) override;
    void visit(Function* node) override;
    void visit(Statement* node) override;
    void visit(Constant* node) override;
    void visit(UnaryOp* node) override;
};

#endif