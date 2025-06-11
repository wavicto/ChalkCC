#ifndef PARSER_HPP    
#define PARSER_HPP

#include "lexical_analysis/lexer.hpp"
#include "syntactic_analysis/c_node.hpp"
#include "syntactic_analysis/c_visitors/c_cleaner.hpp"
#include "syntactic_analysis/c_visitors/c_printer.hpp"

class AST {
    public:

    //Initializes C AST
    AST(std::vector<Token>& tokens);

    ~AST();

    //Prints the C AST structure
    void print();

    //RETURNS: the root program node
    Program* get_root();


    private:
    Program* root;

    //Heper functions used to generate C AST from tokens
    Function* parse_function(std::vector<Token>& tokens);
    Statement* parse_statement(std::vector<Token>& token);
    Expression* parse_expression(std::vector<Token>& tokens);
    UnaryOp* parse_unary(std::vector<Token>& tokens);
    Constant* parse_constant(std::vector<Token>& tokens);
};

#endif