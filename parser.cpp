#include "parser.hpp"

AST::AST(std::vector<Token>& tokens)
    :root(new program)
{
    try {
    root->ptr = parse_function(tokens);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Parser error: " << e.what() << std::endl;
        std::exit(1);
    }}

AST::~AST(){
    Cleaner worker;
    worker.visit(this->root);
}

void AST::print(){
    Traveler person;
    person.visit(this->root);
}

program* AST::get_root(){
    return root;
}

function* AST::parse_function(std::vector<Token>& tokens) {
    function* func = new function;
    bool is_int = tokens[0].expect(Int_key);

    if (!is_int){
        throw std::runtime_error("Invalid return type");
    }

    if (tokens[1].expect(Identifier) &&  tokens[2].expect(Open_parenthesis) && 
        tokens[3].expect(Void_key) && tokens[4].expect(Close_parenthesis) && tokens[5].expect(Open_brace)){
        func->name = tokens[1].get_name();
    }
    else {
        throw std::runtime_error("Expected identifier, (, ), or {");
    }
    
    tokens.erase(tokens.begin(), tokens.begin() + 6);

    func->ptr = parse_statement(tokens);

    if (tokens[0].expect(Close_brace)){
        tokens.erase(tokens.begin());
    }
    else{
        throw std::runtime_error("Expected }");
    }
    return func;
}

statement* AST::parse_statement(std::vector<Token>& tokens){
    statement* state = new statement;

    if(!tokens[0].expect(Return_key)){
        throw std::runtime_error("Expected return key");
    }

    tokens.erase(tokens.begin());

    state->ptr = parse_expression(tokens);

    if(!tokens[0].expect(Semicolon)){
        throw std::runtime_error("Expected ;");
    }
    tokens.erase(tokens.begin());

    return state;
}

expression* AST::parse_expression(std::vector<Token>& tokens){
    expression* ep = new expression;

    if(!tokens[0].expect(Constant)){
        throw std::runtime_error("Expected constant");
    }

    ep->ptr = parse_constant(tokens);
    tokens.erase(tokens.begin());
    return ep;
}

constant* AST::parse_constant(std::vector<Token>& tokens){
    constant* c = new constant;

    c->value = tokens[0].get_value();
    return c;
}

