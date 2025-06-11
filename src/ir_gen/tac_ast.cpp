#include "ir_gen/tac_ast.hpp"

TacAST::~TacAST(){
    TacCleaner cleaner;
    cleaner.visit(root);
    clean_temp_var();
}

TacAST::TacAST(AST &tree)
:temp_var_count(0)
{
    root = gen(tree.get_root());
}

TacProgram* TacAST::get_root(){
    return root;
}

void TacAST::clean_temp_var(){
    for (auto ptr : temp_vars){
        delete ptr;
    }
}

TacProgram* TacAST::gen(Program* node){
    TacProgram* program = new TacProgram;
    program->func_ptr = gen(node->func_ptr);
    return program;
}

TacFunction* TacAST::gen(Function* node){
    TacFunction* func = new TacFunction;
    func->id = node->name;
    gen(node->state_ptr, func->body);
    return func;
}

void TacAST::gen(Statement* node, std::vector<TacInstruction*>& body){
    TacReturn* ret = new TacReturn;
    Expression* exp_ptr = node->exp_ptr;
    ret->val_ptr = exp_ptr->gen(this, body);
    body.push_back(ret);
}

TacVal* TacAST::gen(UnaryOp* node, std::vector<TacInstruction*>& body){
    TacUnary* unary = new TacUnary;
    unary->op = node->type;
    Expression* exp_ptr = node->exp_ptr;
    //Recursive call so that the inner most node is created first
    unary->src = exp_ptr->gen(this, body);
    unary->dst = make_temp_var();
    temp_vars.push_back(unary->dst);
    body.push_back(unary);
    return unary->dst;
}

TacConstant* TacAST::gen(Constant* node){
    TacConstant* constant = new TacConstant;
    constant->value = node->value;
    return constant;
}

TacVar* TacAST::make_temp_var(){
    TacVar* var = new TacVar;
    var->name = "tmp." + std::to_string(temp_var_count);
    temp_var_count++;
    return var;
}

void TacAST::print(){
    TacPrinter p;
    p.visit(root);
}