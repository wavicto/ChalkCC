#ifndef TAC_VISITOR_HPP
#define TAC_VISITOR_HPP

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
    virtual void visit(tac_instruction* node) = 0;
    virtual void visit(tac_return* node) = 0;
    virtual void visit(tac_unary* node) = 0;
    virtual void visit(tac_val* node) = 0;
    virtual void visit(tac_constant* node) = 0;
    virtual void visit(tac_var* node) = 0;

    virtual ~tac_visitor();
};
#endif