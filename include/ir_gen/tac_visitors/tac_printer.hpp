#ifndef TAC_PRINTER_HPP
#define TAC_PRINTER_HPP

#include <iostream>
#include "ir_gen/tac_visitors/tac_visitor.hpp"

//Prints TacAST structure
class TacPrinter : public TacVisitor {
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