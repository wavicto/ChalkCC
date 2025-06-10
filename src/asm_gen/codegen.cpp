#include "asm_gen/codegen.hpp"
#include "ir_gen/tac_ast.hpp"

ASM_AST::ASM_AST(TAC_AST &tree)
    :stack_offset(0)
{
    //Generates inital structure
    root = gen(tree.get_root());

    //First compiler pass that sets pseudo registers to stack locations
    asm_pseudo_locator locator(pseudo_map);
    locator.visit(root);
    clean_map();

    //Second compiler pass that finalizes the assembly instructions
    asm_instruction_finalizer finalizer(stack_offset);
    finalizer.visit(root);
}

ASM_AST::~ASM_AST(){
    asm_cleaner worker;
    worker.visit(this->root);
}

void ASM_AST::asm_gen(){
    asm_generator generator;
    generator.visit(this->root);
}

std::unordered_map<asm_pseudo_reg*, int> ASM_AST::get_pseudo_map(){
    return pseudo_map;
}

void ASM_AST::clean_map(){
    for (auto &ptr : pseudo_map){
        delete ptr.first;
    }
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

    asm_unary* unary_ptr = new asm_unary;
    if (node->op == Complement){
        unary_ptr->op = Not;
    }
    else if (node->op == Negation){
        unary_ptr->op = Neg;
    }
    unary_ptr->operand_ptr = mov->dst;
    instructions.push_back(mov);
    instructions.push_back(unary_ptr);
}

asm_operand* ASM_AST::gen(tac_constant* node){
    asm_imm* literal = new asm_imm;
    literal->value = node->value;
    return literal;
}

asm_operand* ASM_AST::gen(tac_var* node){
    for (auto &element : pseudo_map){
        if ((element.first)->id == node->name){
            return element.first;
        }
    }
    asm_pseudo_reg* r = new asm_pseudo_reg;
    r->id = node->name;
    stack_offset -= 4;
    pseudo_map.insert({r, stack_offset});
    return r;
}