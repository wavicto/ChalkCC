#ifndef LEXER_HPP    
#define LEXER_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include "lexical_analysis/token.hpp"

class lexer {
    public:

    //Initalizes lexer
    lexer();

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
    static std::regex constant;
    static std::regex int_key;
    static std::regex void_key;
    static std::regex return_key;
    static std::regex open_p;
    static std::regex close_p;
    static std::regex open_b;
    static std::regex close_b;
    static std::regex semicol;
    static std::regex complement;
    static std::regex negation;
    static std::regex decrement;

    static std::regex malformed_token;
};

#endif