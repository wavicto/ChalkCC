#ifndef LEXER_HPP    
#define LEXER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include "lexical_analysis/token.hpp"

class Lexer {
    public:

    //Initalizes lexer
    Lexer();

    //RETURNS: a vector of tokens from a file
    std::vector<Token> extract(std::ifstream &file);

    //MODIFIES: determines all possible tokens from "token" and adds it to list 
    void tokenize(std::vector<Token> &list, std::string token);

    //MODIFIES: helper that adds token to a list
    void token_adder(std::vector<Token> &list, std::string token);

    //RETURNS: determines if token matches to any regex
    bool matches(const std::string& token);

    private:
    
    static std::regex id;
    static std::regex constantliteral;
    static std::regex int_key;
    static std::regex void_key;
    static std::regex return_key;
    static std::regex open_parenthesis;
    static std::regex close_parenthesis;
    static std::regex open_brace;
    static std::regex close_brace;
    static std::regex semicolon;
    static std::regex complement;
    static std::regex negation;
    static std::regex decrement;
    static std::regex addition;
    static std::regex multiplication;
    static std::regex division;
    static std::regex modulus;

    static std::regex malformed_token;
};

#endif