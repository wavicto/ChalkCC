#ifndef TAC_CLEANER_HPP
#define TAC_CLEANER_HPP

#include "ir_gen/tac_visitors/tac_visitor.hpp"

//Cleans up dynamically allocated TacAST nodes
class TacCleaner : public TacVisitor {
    public:
    virtual void visit(TacProgram* node) override;
    virtual void visit(TacFunction* node) override;
    virtual void visit(TacReturn* node) override;
    virtual void visit(TacUnary* node) override;
    virtual void visit(TacBinary* node) override;
    virtual void visit(TacConstant* node) override;
    virtual void visit(TacVar* node) override;
};

#endif