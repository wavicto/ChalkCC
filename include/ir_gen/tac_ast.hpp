#ifndef TAC_TREE_HPP    
#define TAC_TREE_HPP

#include "ir_gen/tac_node.hpp"
#include "ir_gen/tac_visitors/tac_cleaner.hpp"
#include "ir_gen/tac_visitors/tac_printer.hpp"
#include "syntactic_analysis/parser.hpp"
#include "syntactic_analysis/c_node.hpp"

//Forward declaration
class AST;

class TacAST {
    public:

    //Initalizes TacAST from C AST
    TacAST(AST &tree);

    ~TacAST();

    //Prints TacAST structure
    void print();

    //RETURNS: the root of TacAST structure
    TacProgram* get_root(); 

    private:
    TacProgram* root;
    int temp_var_count;
    std::vector <TacVal*> temp_vars;

    //Helper functions to generate TacAST from C AST traversal
    TacProgram* gen(Program* node);
    TacFunction* gen(Function* node);
    void gen(Statement* node, std::vector<TacInstruction*>& body);
    TacVal* gen(UnaryOp* node, std::vector<TacInstruction*>& body);
    TacVal* gen(BinaryOp* node, std::vector<TacInstruction*>& body);
    TacConstant* gen(Constant* node);

    TacVar* make_temp_var();
    //MODIFIES: clean up temp_vars as its nodes can be shared among multiple TacInstructions
    void clean_temp_var();

    //Asists with TacAST generation
    friend class BinaryOp;
    friend class Constant;
    friend class UnaryOp;
};

#endif