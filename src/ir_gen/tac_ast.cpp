#include "ir_gen/tac_ast.hpp"

TacAST::TacAST(AST &tree)
:temp_var_count(0)
{
    root = std::unique_ptr<TacProgram>(gen(tree.get_root()));
}

TacProgram* TacAST::get_root(){
    return root.get();
}

TacProgram* TacAST::gen(Program* node){
    TacProgram* program = new TacProgram;
    program->func_ptr = std::unique_ptr<TacFunction>(gen(node->func_ptr.get()));
    return program;
}

TacFunction* TacAST::gen(Function* node){
    TacFunction* func = new TacFunction;
    func->id = node->name;
    gen(node->state_ptr.get(), func->body);
    return func;
}

void TacAST::gen(Statement* node, std::vector<std::unique_ptr<TacInstruction>>& body){
    TacReturn* ret = new TacReturn;
    ret->val_ptr = std::unique_ptr<TacVal>(node->exp_ptr->gen(this, body));
    body.push_back(std::unique_ptr<TacInstruction>(ret));
}

TacVal* TacAST::gen(UnaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body){
    TacUnary* unary = new TacUnary;
    unary->op = node->type;
    //Recursive call so that the inner most node is created first
    unary->src = std::shared_ptr<TacVal>(node->exp_ptr->gen(this, body));
    unary->dst = std::shared_ptr<TacVal>(make_temp_var());
    body.push_back(std::unique_ptr<TacInstruction>(unary));
    return unary->dst.get();
}

TacVal* TacAST::gen(BinaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body){
    TacBinary* binary = new TacBinary;
    binary->src_1 = std::shared_ptr<TacVal>((node->exp_left)->gen(this, body));
    binary->src_2 = std::shared_ptr<TacVal>((node->exp_right)->gen(this, body));
    binary->dst = std::shared_ptr<TacVal>(make_temp_var());
    binary->binary_op = node->op;
    body.push_back(std::unique_ptr<TacInstruction>(binary));
    return binary->dst.get();
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
    p.visit(root.get());
}