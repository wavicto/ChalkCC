#ifndef TAC_PRINTER_HPP
#define TAC_PRINTER_HPP

#include <iostream>
#include "ir_gen/tac_visitors/tac_visitor.hpp"

//Prints TAC_AST structure
class tac_printer : public tac_visitor {
    public:
    virtual void visit(tac_program* node) override;
    virtual void visit(tac_function* node) override;
    virtual void visit(tac_return* node) override;
    virtual void visit(tac_unary* node) override;
    virtual void visit(tac_constant* node) override;
    virtual void visit(tac_var* node) override;
};


#endif