#include "lexer.hpp"

std::regex lexer::id("[a-zA-Z_]\\w*\\b");
std::regex lexer::constant("[0-9]+\\b");
std::regex lexer::int_key("int\\b");
std::regex lexer::void_key("void\\b");
std::regex lexer::open_p("\\(");
std::regex lexer::close_p("\\)");
std::regex lexer::open_b("{");
std::regex lexer::close_b("}");
std::regex lexer::semicol(";");


bool lexer::matches(const std::string& token) {
    if (token.length() == 1){
        return std::regex_match(token, open_b) ||
        std::regex_match(token, close_b) ||
        std::regex_match(token, semicol);
    }
    return std::regex_match(token, id) ||
           std::regex_match(token, constant) ||
           //std::regex_match(token, int_key) ||
           //std::regex_match(token, void_key) ||
           std::regex_match(token, open_p) ||
           std::regex_match(token, close_p);
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
        list.push_back(Token(Identifier, token));
    }
    else if (std::regex_match(token, constant)) {
        list.push_back(Token(Constant, stoi(token)));
    }
    else if (std::regex_match(token, open_p)) {
        list.push_back(Token(open_p));
    }
    else if (std::regex_match(token, close_p)) {
        return true;
    }
}


/*
    Identifier,
    Constant,
    Int_key,
    Void_key,
    Return_key,
    Close_parenthesis,
    Open_brace,
    Close_brace,
    Semicolon
*/


void lexer::tokenize(std::vector<Token> &list, std::string token){
    int start = 0;
    int end = 1;

    while (token.length() != 0){
        while(!matches(token.substr(start, end))){
            end++;
            if (end == token.length() + 1){
                throw std::runtime_error("Lexer: potential source code syntax error");
            }
        }
        while(matches(token.substr(start, end))){
            end++;
        }
        end--;

        token = token.substr(end, token.length() - end);
        end = 1;
    }
    
}

std::vector<Token> lexer::extract(std::ifstream &file){
    std::string section;
    std::vector<Token> list();

    while(file >> section){

    }

}

/*
find longest match at start of input for any regex in Table 1-1
if no match is found, raise an error
convert matching substring into a token
remove matching substring from start of input
*/