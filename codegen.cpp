#include "codegen.hpp"

ASM_AST::ASM_AST(AST &tree)
{
    root = gen(tree.get_root());
}

ASM_AST::~ASM_AST(){
    asm_cleaner worker;
    worker.visit(this->root);
}

void ASM_AST::asm_gen(){
    asm_generator generator;
    generator.visit(this->root);
}

asm_program* ASM_AST::gen(program* node){
    asm_program* root = new asm_program;
    function* ptr = node->ptr;
    if (ptr){
        root->ptr = gen(ptr);
    }
    return root;
}

asm_function* ASM_AST::gen(function* node){
    asm_function* func = new asm_function;
    statement* state = node->ptr;

    if(state){
        expression* exp = state->ptr;
        if (exp){
            func->instructions.push_back(gen(exp));
        }
        func->instructions.push_back(gen(state));
    }
    func->name = node->name;
    return func;
}

asm_instruction* ASM_AST::gen(statement* node){
    asm_instruction* ptr = new asm_instruction;
    ptr->ptr = new asm_ret;
    return ptr;
}

asm_instruction* ASM_AST::gen(expression* node){
    asm_instruction* ptr = new asm_instruction;
    asm_mov* mov = new asm_mov;

    ptr->ptr = mov;

    asm_operand* src = new asm_operand;
    asm_operand* dst = new asm_operand;

    mov->src = src;
    mov->dst = dst;

    asm_imm* v = new asm_imm;
    v->value = node->ptr->value;
    asm_reg* r = new asm_reg;
    r->name = EAX;

    src->ptr = v;
    dst->ptr = r;

    return ptr;

}
