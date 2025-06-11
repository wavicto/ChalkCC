#ifndef TAC_CLEANER_HPP
#define TAC_CLEANER_HPP

#include "ir_gen/tac_visitors/tac_visitor.hpp"

//Cleans up dynamically allocated TAC_AST nodes
class tac_cleaner : public tac_visitor {
    public:
    virtual void visit(tac_program* node) override;
    virtual void visit(tac_function* node) override;
    virtual void visit(tac_return* node) override;
    virtual void visit(tac_unary* node) override;
    virtual void visit(tac_constant* node) override;
    virtual void visit(tac_var* node) override;
};

#endif