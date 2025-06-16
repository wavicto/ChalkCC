#include "asm_gen/codegen.hpp"
#include "ir_gen/tac_ast.hpp"

AsmAST::AsmAST(TacAST &tree)
    :stack_offset(0)
{
    //First compiler pass that generates inital structure
    root = gen(tree.get_root());

    //Second compiler pass that sets pseudo registers to actual stack locations
    AsmPseudoLocator locator(pseudo_map);
    locator.visit(root.get());

    //Third compiler pass that finalizes the assembly instructions
    AsmInstructionFinalizer finalizer(stack_offset);
    try {
        finalizer.visit(root.get());
    } 
    catch (const std::runtime_error& e) {
        std::cerr << "Instruction Finalizer Error: " << e.what() << std::endl;
        std::exit(1);
    }
}

void AsmAST::asm_gen(){
    AsmGenerator generator;
    generator.visit(root.get());
}

std::unordered_map<std::shared_ptr<AsmPseudoReg>, int> AsmAST::get_pseudo_map(){
    return pseudo_map;
}

std::unique_ptr<AsmProgram> AsmAST::gen(TacProgram* node){
    auto root = std::make_unique<AsmProgram>();
    if (node->func_ptr){
        root->func_ptr = gen(node->func_ptr.get());
    }
    return root;
}

std::unique_ptr<AsmFunction> AsmAST::gen(TacFunction* node){
    auto func = std::make_unique<AsmFunction>();
    func->name = node->id;
    for (auto& instruction : node->body){
        instruction->gen(this, func->instructions);
    }
    return func;
}

void AsmAST::gen(TacReturn* node, std::vector<std::unique_ptr<AsmInstruction>> &instructions) {
    auto mov = std::make_unique<AsmMov>();
    mov->src = node->val_ptr->gen(this);
    auto dst = std::make_unique<AsmReg>();;
    dst->name = AX;
    mov->dst = std::move(dst);

    instructions.push_back(std::move(mov));
    instructions.push_back(std::make_unique<AsmRet>());
}

void AsmAST::gen(TacUnary* node, std::vector<std::unique_ptr<AsmInstruction>> &instructions){
    auto mov = std::make_unique<AsmMov>();
    mov->src = node->src->gen(this);
    mov->dst = node->dst->gen(this);

    auto unary_ptr = std::make_unique<AsmUnary>();
    if (node->op == Complement){
        unary_ptr->op = Not;
    }
    else if (node->op == Negation){
        unary_ptr->op = Neg;
    }
    unary_ptr->operand_ptr = mov->dst;
    instructions.push_back(std::move(mov));
    instructions.push_back(std::move(unary_ptr));
}

void AsmAST::gen(TacBinary* node, std::vector<std::unique_ptr<AsmInstruction>> &instructions){
    if (node->binary_op == Division){
        auto mov_1 = std::make_unique<AsmMov>();
        auto mov_2 = std::make_unique<AsmMov>();
        auto div = std::make_unique<Idiv>();
        auto reg = std::make_shared<AsmReg>();
        reg->name = AX;
        mov_1->src = (node->src_1)->gen(this);
        mov_1->dst = reg;
        div->operand_ptr = (node->src_2)->gen(this);
        mov_2->src = reg;
        mov_2->dst = (node->dst)->gen(this);
        instructions.push_back(std::move(mov_1));
        instructions.push_back(std::make_unique<Cdq>());
        instructions.push_back(std::move(div));
        instructions.push_back(std::move(mov_2));
    }
    else if (node->binary_op == Modulus){
        auto mov_1 = std::make_unique<AsmMov>();
        auto mov_2 = std::make_unique<AsmMov>();
        auto div = std::make_unique<Idiv>();
        auto reg_one = std::make_shared<AsmReg>();
        auto reg_two = std::make_shared<AsmReg>();
        reg_one->name = AX;
        reg_two->name = DX;
        mov_1->src = (node->src_1)->gen(this);
        mov_1->dst = reg_one;
        div->operand_ptr = (node->src_2)->gen(this);
        mov_2->src = reg_two;
        mov_2->dst = (node->dst)->gen(this);
        instructions.push_back(std::move(mov_1));
        instructions.push_back(std::make_unique<Cdq>());
        instructions.push_back(std::move(div));
        instructions.push_back(std::move(mov_2));
    }
    else {
        auto mov = std::make_unique<AsmMov>();
        mov->src = (node->src_1)->gen(this);
        mov->dst = (node->dst)->gen(this);
        auto binary =  std::make_unique<AsmBinary>();
        if (node->binary_op == Addition){
            binary->op = Add;
        }
        else if (node->binary_op == Negation){
            binary->op = Sub;
        }
        else if (node->binary_op == Multiplication){
            binary->op = Mult;
        }
        binary->src = (node->src_2)->gen(this);
        binary->dst = mov->dst; 
        instructions.push_back(std::move(mov));
        instructions.push_back(std::move(binary));
    }
}

std::shared_ptr<AsmImm> AsmAST::gen(TacConstant* node){
    auto literal = std::make_shared<AsmImm>();
    literal->value = node->value;
    return literal;
}

std::shared_ptr<AsmPseudoReg> AsmAST::gen(TacVar* node){
    //Checks to see if the node has been previously assigned a pseudo register
    //Due to how TacVar nodes can be shared by multiple tac_instructions
    for (auto &element : pseudo_map){
        if ((element.first)->id == node->name){
            return element.first;
        }
    }
    auto r = std::make_shared<AsmPseudoReg>();
    r->id = node->name;
    stack_offset -= 4;
    pseudo_map.insert({r, stack_offset});
    return r;
}