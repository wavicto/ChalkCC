#include "lexical_analysis/token.hpp"

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

std::string Token::get_type_name(TokenType type) {
    switch (type) {
        case Open_brace: return "Open_brace";
        case Close_brace: return "Close_brace";
        case Semicolon: return "Semicolon";
        case Identifier: return "Identifier";
        case Constant: return "Constant";
        case Int_key: return "Int_key";
        case Void_key: return "Void_key";
        case Return_key: return "Return_key";
        case Open_parenthesis: return "Open_parenthesis";
        case Close_parenthesis: return "Close_parenthesis";
        case Decrement: return "Decrement";
        case Negation: return "Negation";
        case Complement: return "Complement";
        default: return "Invalid";
    }
}

int Token::get_value(){
    assert(get_type() == Constant); 
    return this->value;
}
    
std::string Token::get_name(){
    assert(get_type() == Identifier);
    return this->name;
}

bool Token::expect(TokenType expected){
    return expected == this->get_type();
}

