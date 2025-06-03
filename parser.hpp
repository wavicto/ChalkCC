#ifndef PARSER_HPP    
#define PARSER_HPP

#include "lexer.hpp"
#include "c_node.hpp"

class AST {
    public:

    AST(std::vector<Token>& tokens);

    ~AST();

    void print();
    program* get_root();


    private:
    program* root;

    function* parse_function(std::vector<Token>& tokens);
    statement* parse_statement(std::vector<Token>& token);
    expression* parse_expression(std::vector<Token>& tokens);
    constant* parse_constant(std::vector<Token>& tokens);
};

#endif