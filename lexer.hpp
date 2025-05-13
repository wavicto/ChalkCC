#include <fstream>
#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include "token.hpp"

class lexer {
    public:

    lexer();

    std::vector<Token> extract(std::ifstream &file);

    void tokenize(std::vector<Token> &list, std::string token);

    void token_adder(std::vector<Token> &list, std::string token);

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
};