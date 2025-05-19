#include "lexer.hpp"

std::regex lexer::id("[a-zA-Z_]\\w*\\b");
std::regex lexer::constant("[0-9]+\\b");
std::regex lexer::int_key("int\\b");
std::regex lexer::void_key("void\\b");
std::regex lexer::return_key("return\\b");
std::regex lexer::open_p("\\(");
std::regex lexer::close_p("\\)");
std::regex lexer::open_b("\\{");
std::regex lexer::close_b("\\}");
std::regex lexer::semicol(";");

//malformed token check
std::regex lexer::malformed_token("[0-9]+[a-zA-Z_]\\w*\\b");

lexer::lexer(){

}

std::vector<Token> lexer::extract(std::ifstream &file){
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

void lexer::tokenize(std::vector<Token> &list, std::string token){
    int start = 0;
    int end = 1;

    while (token.length() != 0){
        std::string subtoken = token.substr(start, end);
        //searches for first valid token
        while(!matches(subtoken)){
            end++;
            subtoken = token.substr(start, end);
            if (end == token.length() + 1){
                throw std::runtime_error("Invalid Token");
            }
        }
        //extends to determine if a longer token could be found
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

bool lexer::matches(const std::string& token) {
    if (std::regex_match(token, malformed_token)){
        throw std::runtime_error("Malformed Token");
    }

    bool result = std::regex_match(token, open_b) ||
    std::regex_match(token, close_b) ||
    std::regex_match(token, semicol) ||
    std::regex_match(token, id) ||
    std::regex_match(token, constant) ||
    std::regex_match(token, open_p) ||
    std::regex_match(token, close_p);

    return result;
}

void lexer::token_adder(std::vector<Token> &list, std::string token){
    if (std::regex_match(token, open_b)) {
        list.push_back(Token(Open_brace));
    }
    else if (std::regex_match(token, close_b)) {
        list.push_back(Token(Close_brace));
    }
    else if (std::regex_match(token, semicol)) {
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
    else if (std::regex_match(token, constant)) {
        list.push_back(Token(Constant, stoi(token)));
    }
    else if (std::regex_match(token, open_p)) {
        list.push_back(Token(Open_parenthesis));
    }
    else if (std::regex_match(token, close_p)) {
        list.push_back(Token(Close_parenthesis));
    }
}
