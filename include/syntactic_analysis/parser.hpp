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
    
    // Helper functions used to generate C AST from tokens
    std::unique_ptr<Function> parse_function(std::vector<Token>& tokens);
    std::unique_ptr<Statement> parse_statement(std::vector<Token>& tokens);
    // Factors are constants, unary expressions, or parenthesized expressions
    // Used to help implement precedence climbing
    std::unique_ptr<Expression> parse_factor(std::vector<Token>& tokens);
    std::unique_ptr<Expression> parse_expression(std::vector<Token>& tokens, int min_precedence);
    std::unique_ptr<UnaryOp> parse_unary(std::vector<Token>& tokens);
    std::unique_ptr<Constant> parse_constant(std::vector<Token>& tokens);
};

#endif