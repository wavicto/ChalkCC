#include "ir_gen/tac_ast.hpp"

TacAST::TacAST(AST &tree)
:temp_var_count(0)
{
    root = gen(tree.get_root());
}

TacProgram* TacAST::get_root(){
    return root.get();
}

std::unique_ptr<TacProgram> TacAST::gen(Program* node){
    auto program = std::make_unique<TacProgram>();
    program->func_ptr = gen(node->func_ptr.get());
    return program;
}

std::unique_ptr<TacFunction> TacAST::gen(Function* node){
    auto func = std::make_unique<TacFunction>();
    func->id = node->name;
    gen(node->state_ptr.get(), func->body);
    return func;
}

void TacAST::gen(Statement* node, std::vector<std::unique_ptr<TacInstruction>>& body){
    auto ret = std::make_unique<TacReturn>();
    ret->val_ptr = node->exp_ptr->gen(this, body);
    body.push_back(std::move(ret));
}

std::shared_ptr<TacVal> TacAST::gen(UnaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body){
    auto unary = std::make_unique<TacUnary>();
    unary->op = node->type;
    //Recursive call so that the inner most node is created first
    unary->src = node->exp_ptr->gen(this, body);
    unary->dst = make_temp_var();
    std::shared_ptr<TacVal> result = unary->dst;
    body.push_back(std::move(unary));
    return result;
}

std::shared_ptr<TacVal> TacAST::gen(BinaryOp* node, std::vector<std::unique_ptr<TacInstruction>>& body){
    auto binary = std::make_unique<TacBinary>();
    binary->src_1 = node->exp_left->gen(this, body);
    binary->src_2 = node->exp_right->gen(this, body);
    binary->dst = make_temp_var();
    binary->binary_op = node->op;
    std::shared_ptr<TacVal> result = binary->dst;
    body.push_back(std::move(binary));
    return result;
}

std::shared_ptr<TacConstant> TacAST::gen(Constant* node){
    auto constant = std::make_shared<TacConstant>();
    constant->value = node->value;
    return constant;
}

std::shared_ptr<TacVar> TacAST::make_temp_var(){
    auto var = std::make_shared<TacVar>();
    var->name = "tmp." + std::to_string(temp_var_count);
    temp_var_count++;
    return var;
}

void TacAST::print(){
    TacPrinter p;
    p.visit(root.get());
}