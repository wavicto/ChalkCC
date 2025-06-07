#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"

    /*
    Command line options:
    -lex       Run the lexer only. Displays the tokens generated.
    -parse     Run the lexer and parser. Displays C AST.
    -codegen   Run the lexer, parser, and generate assembly file. Stops before executable generation.
    */

int main(int argc, char *argv[]) {

    //preprocesses and suppresses line directives
    std::string preprocessing = "gcc -E -P " + std::string(argv[1]) + " -o preprocessed_file.i";
    system(preprocessing.c_str());

    std::ifstream preprocessed_file("preprocessed_file.i");

    lexer lex = lexer();
    std::vector<Token> tokens = lex.extract(preprocessed_file);
    AST tree(tokens);
    tree.print();
    system("rm preprocessed_file.i");
    return 0;
}