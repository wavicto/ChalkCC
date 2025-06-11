#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "lexical_analysis/lexer.hpp"
#include "syntactic_analysis/parser.hpp"
#include "ir_gen/tac_ast.hpp"
#include "asm_gen/codegen.hpp"

    /*
    Command line options:
    -lex       Run the lexer only. Displays the tokens generated.
    -parse     Run the lexer and parser. Displays C AST.
    -codegen   Run the lexer, parser, and generate assembly file. Stops before executable generation.
    */

int main(int argc, char *argv[]) {

    if (!(argc == 2 || argc == 3)) {
        std::cout << "Invalid # of arguments";
        return 1;
    }

    //preprocesses and suppresses line directives
    std::string preprocessing = "gcc -E -P " + std::string(argv[1]) + " -o preprocessed_file.i";
    system(preprocessing.c_str());

    std::ifstream preprocessed_file("preprocessed_file.i");

    if (!preprocessed_file.is_open()) {
        std::cerr << "Error: Could not open preprocessed file" << std::endl;
        return 1;
    }

    if (argc == 3){
        std::string option = argv[2];

        if (option == "-lex"){
            Lexer lex = Lexer();
            std::vector<Token> tokens = lex.extract(preprocessed_file);

            if (tokens.empty()) {
                std::cout << "No tokens found." << std::endl;
            } else {
                for (auto& token : tokens) {
                    std::cout << "Token type: " << token.get_type_name(token.get_type()) << std::endl;
                    if (token.get_type_name(token.get_type()) == "Constant"){
                        std::cout << " Value: " << token.get_value() << std::endl;
                    } 
                }
            }
            return 0;
        }
        else if (option == "-parse"){
            Lexer lex = Lexer();
            std::vector<Token> tokens = lex.extract(preprocessed_file);
            AST tree(tokens);
            tree.print();
            system("rm preprocessed_file.i");
            return 0;
        }
        else if (option == "-codegen"){
            Lexer lex = Lexer();
            std::vector<Token> tokens = lex.extract(preprocessed_file);
            AST tree(tokens);
            TacAST IR(tree);
            AsmAST a(IR);
            a.asm_gen();
            system("rm preprocessed_file.i");
            return 0;
        }
        else {
            std::cout << "ERROR. EXPECTED -lex, -parse, or -codegen";
            return 1;
        }
    }

    std::filesystem::path input_path(argv[1]);
    std::string directory = input_path.parent_path().string();
    std::string name = input_path.stem().string();

    //Compiles the preprocessed file and outputs an assembly file
    Lexer lex = Lexer();
    std::vector<Token> tokens = lex.extract(preprocessed_file);
    AST tree(tokens);
    TacAST IR(tree);
    AsmAST a(IR);
    a.asm_gen();

    //Produce an executable file
    std::string assemble_link = "gcc assembly.s -o " + directory + "/" + name;

    system(assemble_link.c_str());

    system("rm preprocessed_file.i");
    system("rm assembly.s");

    return 0;
}