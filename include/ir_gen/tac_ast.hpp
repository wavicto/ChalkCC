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
    //Raw ptrs are passed as ownership is not transferred.
    std::unique_ptr<TacProgram> gen(Program* node);
    std::unique_ptr<TacFunction> gen(Function* node);
    void gen(Statement* node, std::vector<std::unique_ptr<TacInstruction>>& body);
    std::shared_ptr<TacVal> gen(UnaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body);
    std::shared_ptr<TacVal> gen(BinaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body);
    std::shared_ptr<TacConstant> gen(Constant* node);

    //Makes a temp var
    std::shared_ptr<TacVar> make_temp_var();

    //Asists with TacAST generation
    friend class BinaryOp;
    friend class Constant;
    friend class UnaryOp;
};

#endif