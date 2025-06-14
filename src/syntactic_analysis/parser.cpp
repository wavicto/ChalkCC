#include "syntactic_analysis/parser.hpp"

AST::AST(std::vector<Token>& tokens)
    :root(new Program)
{
    precedence_map.insert({Multiplication, 50});
    precedence_map.insert({Division, 50});
    precedence_map.insert({Modulus, 50});
    precedence_map.insert({Addition, 45});
    precedence_map.insert({Negation, 45});   
     
    try {
    root->func_ptr = parse_function(tokens);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Parser error: " << e.what() << std::endl;
        std::exit(1);
    }
}

AST::~AST(){
    CCleaner cleaner;
    cleaner.visit(this->root);
}

void AST::print(){
    CPrinter printer;
    printer.visit(this->root);
}

Program* AST::get_root(){
    return root;
}

Function* AST::parse_function(std::vector<Token>& tokens) {
    Function* func = new Function;
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

    func->state_ptr = parse_statement(tokens);

    if (tokens[0].expect(Close_brace)){
        tokens.erase(tokens.begin());
    }
    else{
        throw std::runtime_error("Expected }");
    }
    return func;
}

Statement* AST::parse_statement(std::vector<Token>& tokens){
    Statement* state = new Statement;

    if(!tokens[0].expect(Return_key)){
        throw std::runtime_error("Expected return key");
    }

    tokens.erase(tokens.begin());

    state->exp_ptr = parse_expression(tokens, 0);

    if(!tokens[0].expect(Semicolon)){
        throw std::runtime_error("Expected ;");
    }
    tokens.erase(tokens.begin());

    return state;
}

Expression* AST::parse_factor(std::vector<Token>& tokens){
    Expression* exp = nullptr;

    if(tokens[0].expect(ConstantLiteral)){
        exp = parse_constant(tokens);
        tokens.erase(tokens.begin());
        return exp;
    }
    else if (tokens[0].expect(Negation) || tokens[0].expect(Complement)){
        exp = parse_unary(tokens);
        return exp;
    }
    else if (tokens[0].expect(Open_parenthesis)){
        tokens.erase(tokens.begin());
        exp = parse_expression(tokens, 0);
        if(!tokens[0].expect(Close_parenthesis)){
            throw std::runtime_error("Expected )");
        }
        tokens.erase(tokens.begin());
        return exp;
    }
    else {
        throw std::runtime_error("Malformed Factor. Expected constant, unary operator, or (");
    }
}

/*
A BinaryOp's RHS expression can only contain a single factor or an operation with greater precedence
LHS can only contain a single factor or an operation with equal or lower precedence
Using postorder traversal through the AST, operation precedence will be maintained by the tree's grouped structure
*/
Expression* AST::parse_expression(std::vector<Token>& tokens, int min_precedence){
    Expression* left_exp = nullptr;

    left_exp = parse_factor(tokens);

    while (((tokens[0].expect(Addition)) || (tokens[0].expect(Negation)) || (tokens[0].expect(Modulus))
    || (tokens[0].expect(Multiplication)) || (tokens[0].expect(Division))) &&
    precedence_map[tokens[0].get_type()] >= min_precedence){
        BinaryOp* b_op = new BinaryOp;
        b_op->op = tokens[0].get_type();
        int prec =  precedence_map[b_op->op];
        tokens.erase(tokens.begin());
        //prec + 1 enforces left-associativity
        b_op->exp_right = parse_expression(tokens, prec + 1);
        b_op->exp_left = left_exp;
        //Updates for left-associativity
        left_exp = b_op;
    }
    return left_exp;
}

UnaryOp* AST::parse_unary(std::vector<Token>& tokens){
    UnaryOp* ptr = new UnaryOp;
    if (tokens[0].expect(Negation)){
        ptr->type = Negation;
        tokens.erase(tokens.begin());
    }
    else if (tokens[0].expect(Complement)){
        ptr->type = Complement;
        tokens.erase(tokens.begin());
    }
    ptr->exp_ptr = parse_factor(tokens);
    return ptr;
}


Constant* AST::parse_constant(std::vector<Token>& tokens){
    Constant* c = new Constant;
    c->value = tokens[0].get_value();
    return c;
}

