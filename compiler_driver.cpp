#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>

int main(int argc, char *argv[]) {

    /*
    Command line options:
    --lex       Run the lexer only. Stops before parsing.
    --parse     Run the lexer and parser. Stops before assembly generation.
    --codegen   Run the lexer, parser, and generate the assembly, but stop
                before emitting final machine code.
    */

    bool lex = false;
    bool parse = false;
    bool codegen = false;

    if (!(argc == 2 || argc == 3)) {
        std::cout << "Invalid # of arguments";
        return 1;
    }

    if (argc == 3){
        std::string option = argv[2];
        if (option == "--lex"){
            lex = true;
        }
        else if (option == "--pasrse"){
            parse = true;
        }
        else if (option == "--codegen"){
            codegen = true;
        }
    }

    std::filesystem::path input_path(argv[1]);
    std::string directory = input_path.parent_path().string();
    std::string name = input_path.stem().string();

    //preprocesses and suppresses line directives
    std::string preprocessing = "gcc -E -P " + std::string(argv[1]) + " -o preprocessed_file.i";
    system(preprocessing.c_str());

    //compile the preprocessed file and outputs an assemly file
    system("gcc -S preprocessed_file.i -o assembly.s");

    system("rm preprocessed_file.i");

    //produce an executable file
    std::string assemble_link = "gcc assembly.s -o " + directory + "/" + name;

    system(assemble_link.c_str());
    return 0;
}