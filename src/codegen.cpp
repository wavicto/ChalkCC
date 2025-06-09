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

asm_program* ASM_AST::gen(tac_program* node){
    asm_program* root = new asm_program;
    tac_function* ptr = node->func_ptr;
    if (ptr){
        root->func_ptr = gen(ptr);
    }
    return root;
}

asm_function* ASM_AST::gen(tac_function* node){
    asm_function* func = new asm_function;
    func->name = node->id;
    for (auto& instruction : node->body){
        instruction->gen(this, func->instructions);
    }
    return func;
}

void ASM_AST::gen(tac_return* node, std::vector <asm_instruction*> &instructions) {
    asm_mov* mov = new asm_mov;
    tac_val* val = node->val_ptr;
    mov->src = val->gen(this);
    asm_reg* dst = new asm_reg;
    dst->name = AX;
    mov->dst = dst;

    instructions.push_back(mov);
    instructions.push_back(new asm_ret);
}

void ASM_AST::gen(tac_unary* node, std::vector <asm_instruction*> &instructions){
    asm_mov* mov = new asm_mov;
    tac_val* src = node->src;
    tac_val* dst = node->dst;
    mov->src = src->gen(this);
    mov->dst = dst->gen(this);
    
    instructions.push_back(mov);

}


/*
Unary(unary_operator, src, dst)
    Mov(src, dst)
    Unary(unary_operator, dst)
*/

asm_operand* ASM_AST::gen(tac_constant* node){
    asm_imm* literal = new asm_imm;
    literal->value = node->value;
    return literal;
}

asm_operand* ASM_AST::gen(tac_var* node){
    asm_pseudo_reg* r = new asm_pseudo_reg;
    r->id = node->name;
    return r;
}