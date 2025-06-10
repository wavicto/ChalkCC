#ifndef TAC_VISITOR_HPP
#define TAC_VISITOR_HPP

#include <iostream>

//forward declaration
class tac_program;
class tac_function;
class tac_instruction;
class tac_return;
class tac_unary;
class tac_val;
class tac_constant;
class tac_var;

class tac_visitor {
    public:
    virtual void visit(tac_program* node) = 0;
    virtual void visit(tac_function* node) = 0;
    virtual void visit(tac_return* node) = 0;
    virtual void visit(tac_unary* node) = 0;
    virtual void visit(tac_constant* node) = 0;
    virtual void visit(tac_var* node) = 0;

    virtual ~tac_visitor();
};

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