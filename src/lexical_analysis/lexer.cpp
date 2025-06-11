#include "lexical_analysis/lexer.hpp"

std::regex Lexer::id("[a-zA-Z_]\\w*\\b");
std::regex Lexer::constantliteral("[0-9]+\\b");
std::regex Lexer::int_key("int\\b");
std::regex Lexer::void_key("void\\b");
std::regex Lexer::return_key("return\\b");
std::regex Lexer::open_parenthesis("\\(");
std::regex Lexer::close_parenthesis("\\)");
std::regex Lexer::open_brace("\\{");
std::regex Lexer::close_brace("\\}");
std::regex Lexer::semicolon(";");
std::regex Lexer::complement("~");
std::regex Lexer::negation("-");
std::regex Lexer::decrement("--");
std::regex Lexer::addition("\\+");
std::regex Lexer::multiplication("\\*");
std::regex Lexer::division("\\/");
std::regex Lexer::modulus("\\%");
std::regex Lexer::malformed_token("[0-9]+[a-zA-Z_]\\w*\\b");

Lexer::Lexer(){}

std::vector<Token> Lexer::extract(std::ifstream &file){
    std::string section;
    std::vector<Token> list;

    while(file >> section){
        try {
        tokenize(list, section);
        } 
        catch (const std::runtime_error& e) {
            std::cerr << "Lexer error: " << e.what() << std::endl;
            std::exit(1);
        }
    }
    return list;
}

void Lexer::tokenize(std::vector<Token> &list, std::string token){
    int start = 0;
    int end = 1;

    while (token.length() != 0){
        std::string subtoken = token.substr(start, end);
        //Searches for first valid token
        while(!matches(subtoken)){
            end++;
            subtoken = token.substr(start, end);
            if (end == token.length() + 1){
                throw std::runtime_error("Invalid Token");
            }
        }
        //Extends to determine if a longer token could be found
        while(matches(subtoken)){
            if (end == token.length()+1){
                break;
            }
            end++;
            subtoken = token.substr(start, end);
        }
        end--;
        token_adder(list, token.substr(start, end));
        token = token.substr(end, token.length() - end);
        end = 1;
    }
    
}

bool Lexer::matches(const std::string& token) {
    if (std::regex_match(token, malformed_token)){
        throw std::runtime_error("Malformed Token");
    }

    bool result = std::regex_match(token, addition) ||
    std::regex_match(token, multiplication) ||
    std::regex_match(token, division) ||
    std::regex_match(token, modulus) ||
    std::regex_match(token, decrement) ||
    std::regex_match(token, negation) ||
    std::regex_match(token, complement) ||
    std::regex_match(token, open_brace) ||
    std::regex_match(token, close_brace) ||
    std::regex_match(token, semicolon) ||
    std::regex_match(token, id) ||
    std::regex_match(token, constantliteral) ||
    std::regex_match(token, open_parenthesis) ||
    std::regex_match(token, close_parenthesis);

    return result;
}

void Lexer::token_adder(std::vector<Token> &list, std::string token){
    if (std::regex_match(token, open_brace)) {
        list.push_back(Token(Open_brace));
    }
    else if (std::regex_match(token, close_brace)) {
        list.push_back(Token(Close_brace));
    }
    else if (std::regex_match(token, semicolon)) {
        list.push_back(Token(Semicolon));
    }
    else if (std::regex_match(token, id)) {
        if (std::regex_match(token, int_key)){
            list.push_back(Token(Int_key));
        }
        else if(std::regex_match(token, void_key)){
            list.push_back(Token(Void_key));
        }
        else if (std::regex_match(token, return_key)){
            list.push_back(Token(Return_key));
        }
        else{
            list.push_back(Token(Identifier, token));
        }
    }
    else if (std::regex_match(token, constantliteral)) {
        list.push_back(Token(ConstantLiteral, stoi(token)));
    }
    else if (std::regex_match(token, open_parenthesis)) {
        list.push_back(Token(Open_parenthesis));
    }
    else if (std::regex_match(token, close_parenthesis)) {
        list.push_back(Token(Close_parenthesis));
    }
    else if (std::regex_match(token, complement)){
        list.push_back(Token(Complement));
    }
    else if (std::regex_match(token, negation)){
        list.push_back(Token(Negation));
    }
    else if (std::regex_match(token, decrement)){
        list.push_back(Token(Decrement));
    }
    else if (std::regex_match(token, addition)){
        list.push_back(Token(Addition));
    }
    else if (std::regex_match(token, multiplication)){
        list.push_back(Token(Multiplication));
    }
    else if (std::regex_match(token, division)){
        list.push_back(Token(Division));
    }
    else if (std::regex_match(token, modulus)){
        list.push_back(Token(Modulus));
    }
}
