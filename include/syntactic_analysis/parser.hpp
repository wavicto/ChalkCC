#ifndef PARSER_HPP    
#define PARSER_HPP

#include "lexical_analysis/lexer.hpp"
#include "syntactic_analysis/c_node.hpp"
#include "syntactic_analysis/c_visitors/c_printer.hpp"
#include <unordered_map>

class AST {
    public:

    //Initializes C AST
    AST(std::vector<Token>& tokens);

    //Prints the C AST structure
    void print();

    //RETURNS: the root program node
    Program* get_root();

    private:
    std::unique_ptr<Program> root;
    std::unordered_map <TokenType, int> precedence_map;
    
    //Heper functions used to generate C AST from tokens
    Function* parse_function(std::vector<Token>& tokens);
    Statement* parse_statement(std::vector<Token>& token);
    //Factors are constants, unary expressions, or parenthesized expressions
    //Used to help implement precedence climbing
    Expression* parse_factor(std::vector<Token>& tokens);
    Expression* parse_expression(std::vector<Token>& tokens, int min_precedence);
    UnaryOp* parse_unary(std::vector<Token>& tokens);
    Constant* parse_constant(std::vector<Token>& tokens);
};

#endif