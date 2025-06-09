#ifndef TAC_TREE_HPP    
#define TAC_TREE_HPP

#include "tac_node.hpp"
#include "tac_visitor.hpp"
#include "parser.hpp"
#include "c_node.hpp"

//forward declaration as some AST methods depend on TAC_AST
class AST;

class TAC_AST {
    public:

    TAC_AST(AST &tree);

    ~TAC_AST();

    void print();

    tac_program* get_root(); 

    private:
    tac_program* root;
    int temp_var_count;
    std::vector <tac_val*> temp_vars;

    tac_program* gen(program* node);
    tac_function* gen(function* node);
    void gen(statement* node, std::vector<tac_instruction*>& body);
    tac_val* gen(unary_op* node, std::vector<tac_instruction*>& body);
    tac_constant* gen(constant* node);
    

    tac_var* make_temp_var();
    void clean_temp_var();

    //expression nodes are given friend for polymorphism
    friend class constant;
    friend class unary_op;
};

#endif