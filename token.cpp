#include "token.hpp"

Token::Token(TokenType t) 
    : type(t), value(0), name("") {

    }

Token::Token(TokenType t, int value)
    : type(t), value(value), name(""){

    }

Token::Token(TokenType t, std::string name)
    : type(t), value(0), name(name){

    }

TokenType Token::get_type(){
    return this->type;
}

int Token::get_value(){
    assert(get_type() == Constant); 
    return this->value;
}
    
std::string Token::get_name(){
    assert(get_type() == Identifier);
    return this->name;
}
