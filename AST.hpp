#ifndef AST_HPP    
#define AST_HPP

#include "lexer.hpp"
#include "node.hpp"

class AST {
    public:

    AST();

    void visit();

    private:
    ASTNode* root;
};


#endif