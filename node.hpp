#ifndef NODE_HPP    
#define NODE_HPP

#include <vector>
#include <string>

//establish a visitor class later 
//refer to JONES AST impl for documentation

class ASTNode {
    public:
    virtual ~ASTNode(){}
};

class program : public ASTNode {
    public:

    function* ptr;

};

class function : public ASTNode {
    public:

    statement* ptr;
    std::string name;
};

class statement: public ASTNode {
    public:

    return_statement* ptr;
};

class expression: public ASTNode {
    public:

    constant* ptr;

};

class constant : public expression {
    public:

    int value;

};

class return_statement: public statement {
    public:

};


#endif