#ifndef TOKEN_HPP    
#define TOKEN_HPP

#include <string>
#include <cassert>


//Lexer TokenTypes
enum TokenType {
    Identifier,
    Constant,
    Int_key,
    Void_key,
    Return_key,
    Close_parenthesis,
    Open_brace,
    Close_brace,
    Semicolon

};

class Token {
    public:

    Token(TokenType t);

    Token(TokenType t, int value);

    Token(TokenType t, std::string name);

    TokenType get_type();

    int get_value();
    
    std::string get_name();

    private:
    TokenType type;
    int value;
    std::string name;

};

#endif