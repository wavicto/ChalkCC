#include "tac_ast.hpp"

TAC_AST::~TAC_AST(){
    tac_cleaner cleaner;
    cleaner.visit(root);
    clean_temp_var();
}

TAC_AST::TAC_AST(AST &tree)
:temp_var_count(0)
{
    root = gen(tree.get_root());
}

void TAC_AST::clean_temp_var(){
    for (auto ptr : temp_vars){
        delete ptr;
    }
}

tac_program* TAC_AST::gen(program* node){
    tac_program* program = new tac_program;
    program->func_ptr = gen(node->func_ptr);
    return program;
}

tac_function* TAC_AST::gen(function* node){
    tac_function* func = new tac_function;
    func->id = node->name;
    gen(node->state_ptr, func->body);
    return func;
}

void TAC_AST::gen(statement* node, std::vector<tac_instruction*>& body){
    tac_return* ret = new tac_return;
    ret->val_ptr = gen(node->exp_ptr, body);
    body.push_back(ret);
}

tac_val* TAC_AST::gen(expression* node,  std::vector<tac_instruction*>& body){
    tac_val* value = nullptr;
    if (auto ptr = dynamic_cast<constant*>(node)) {
        value = gen(ptr);
    } else if (auto ptr = dynamic_cast<unary_op*>(node)) {
        tac_unary* unary = new tac_unary;
        unary->op = ptr->type;
        //recursive call so that the inner most node is created first
        unary->src = gen(ptr->exp_ptr, body);
        unary->dst = make_temp_var();
        value = unary->dst;
        temp_vars.push_back(unary->dst);
        body.push_back(unary);
    }
    return value;
}

tac_constant* TAC_AST::gen(constant* node){
    tac_constant* constant = new tac_constant;
    constant->value = node->value;
    return constant;
}

tac_var* TAC_AST::make_temp_var(){
    tac_var* var = new tac_var;
    var->name = "tmp." + std::to_string(temp_var_count);
    temp_var_count++;
    return var;
}

void TAC_AST::print(){
    tac_printer p;
    p.visit(root);
}