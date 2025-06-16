#ifndef TAC_TREE_HPP    
#define TAC_TREE_HPP

#include "ir_gen/tac_node.hpp"
#include "ir_gen/tac_visitors/tac_printer.hpp"
#include "syntactic_analysis/parser.hpp"
#include "syntactic_analysis/c_node.hpp"

//Forward declaration
class AST;

class TacAST {
    public:

    //Initalizes TacAST from C AST
    TacAST(AST &tree);

    //Prints TacAST structure
    void print();

    //RETURNS: the root of TacAST structure
    TacProgram* get_root(); 

    private:
    std::unique_ptr<TacProgram> root;
    int temp_var_count;

    //Helper functions to generate TacAST from C AST traversal
    TacProgram* gen(Program* node);
    TacFunction* gen(Function* node);
    void gen(Statement* node, std::vector<std::unique_ptr<TacInstruction>>& body);
    TacVal* gen(UnaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body);
    TacVal* gen(BinaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body);
    TacConstant* gen(Constant* node);

    //Makes a temp var
    TacVar* make_temp_var();

    //Asists with TacAST generation
    friend class BinaryOp;
    friend class Constant;
    friend class UnaryOp;
};

#endif