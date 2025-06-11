#include "ir_gen/tac_ast.hpp"

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

tac_program* TAC_AST::get_root(){
    return root;
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
    expression* exp_ptr = node->exp_ptr;
    ret->val_ptr = exp_ptr->gen(this, body);
    body.push_back(ret);
}

tac_val* TAC_AST::gen(unary_op* node, std::vector<tac_instruction*>& body){
    tac_unary* unary = new tac_unary;
    unary->op = node->type;
    expression* exp_ptr = node->exp_ptr;
    //Recursive call so that the inner most node is created first
    unary->src = exp_ptr->gen(this, body);
    unary->dst = make_temp_var();
    temp_vars.push_back(unary->dst);
    body.push_back(unary);
    return unary->dst;
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