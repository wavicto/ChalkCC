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
    program* get_root();


    private:
    program* root;

    //Heper functions used to generate AST from tokens
    function* parse_function(std::vector<Token>& tokens);
    statement* parse_statement(std::vector<Token>& token);
    expression* parse_expression(std::vector<Token>& tokens);
    unary_op* parse_unary(std::vector<Token>& tokens);
    constant* parse_constant(std::vector<Token>& tokens);
};

#endif