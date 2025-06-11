#include "asm_gen/codegen.hpp"
#include "ir_gen/tac_ast.hpp"

AsmAST::AsmAST(TacAST &tree)
    :stack_offset(0)
{
    //First compiler pass that generates inital structure
    root = gen(tree.get_root());

    //Second compiler pass that sets pseudo registers to actual stack locations
    AsmPseudoLocator locator(pseudo_map);
    locator.visit(root);
    clean_map();

    //Third compiler pass that finalizes the assembly instructions
    AsmInstructionFinalizer finalizer(stack_offset);
    finalizer.visit(root);
}

AsmAST::~AsmAST(){
    AsmCleaner worker;
    worker.visit(this->root);
}

void AsmAST::asm_gen(){
    AsmGenerator generator;
    generator.visit(this->root);
}

std::unordered_map<AsmPseudoReg*, int> AsmAST::get_pseudo_map(){
    return pseudo_map;
}

void AsmAST::clean_map(){
    for (auto &ptr : pseudo_map){
        delete ptr.first;
    }
}

AsmProgram* AsmAST::gen(TacProgram* node){
    AsmProgram* root = new AsmProgram;
    TacFunction* ptr = node->func_ptr;
    if (ptr){
        root->func_ptr = gen(ptr);
    }
    return root;
}

AsmFunction* AsmAST::gen(TacFunction* node){
    AsmFunction* func = new AsmFunction;
    func->name = node->id;
    for (auto& instruction : node->body){
        instruction->gen(this, func->instructions);
    }
    return func;
}

void AsmAST::gen(TacReturn* node, std::vector <AsmInstruction*> &instructions) {
    AsmMov* mov = new AsmMov;
    TacVal* val = node->val_ptr;
    mov->src = val->gen(this);
    AsmReg* dst = new AsmReg;
    dst->name = AX;
    mov->dst = dst;

    instructions.push_back(mov);
    instructions.push_back(new AsmRet);
}

void AsmAST::gen(TacUnary* node, std::vector <AsmInstruction*> &instructions){
    AsmMov* mov = new AsmMov;
    TacVal* src = node->src;
    TacVal* dst = node->dst;
    mov->src = src->gen(this);
    mov->dst = dst->gen(this);

    AsmUnary* unary_ptr = new AsmUnary;
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

AsmOperand* AsmAST::gen(TacConstant* node){
    AsmImm* literal = new AsmImm;
    literal->value = node->value;
    return literal;
}

AsmOperand* AsmAST::gen(TacVar* node){
    //Checks to see if the node has been previously assigned a pseudo register
    //Due to how TacVar nodes can be shared by multiple tac_instructions
    for (auto &element : pseudo_map){
        if ((element.first)->id == node->name){
            return element.first;
        }
    }
    AsmPseudoReg* r = new AsmPseudoReg;
    r->id = node->name;
    stack_offset -= 4;
    pseudo_map.insert({r, stack_offset});
    return r;
}