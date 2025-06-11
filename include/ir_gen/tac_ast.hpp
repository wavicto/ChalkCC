#ifndef TAC_TREE_HPP    
#define TAC_TREE_HPP

#include "ir_gen/tac_node.hpp"
#include "ir_gen/tac_visitors/tac_cleaner.hpp"
#include "ir_gen/tac_visitors/tac_printer.hpp"
#include "syntactic_analysis/parser.hpp"
#include "syntactic_analysis/c_node.hpp"

//Forward declaration
class AST;

class TAC_AST {
    public:

    //Initalizes TAC_AST from C AST
    TAC_AST(AST &tree);

    ~TAC_AST();

    //Prints TAC_AST structure
    void print();

    //RETURNS: the root of TAC_AST structure
    tac_program* get_root(); 

    private:
    tac_program* root;
    int temp_var_count;
    std::vector <tac_val*> temp_vars;

    //Helper functions to generate TAC_AST from C_AST traversal
    tac_program* gen(program* node);
    tac_function* gen(function* node);
    void gen(statement* node, std::vector<tac_instruction*>& body);
    tac_val* gen(unary_op* node, std::vector<tac_instruction*>& body);
    tac_constant* gen(constant* node);

    tac_var* make_temp_var();
    //MODIFIES: clean up temp_vars as its nodes can be shared among multiple tac_instructions
    void clean_temp_var();

    //Asists with TAC_AST generation
    friend class constant;
    friend class unary_op;
};

#endif