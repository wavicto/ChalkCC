#ifndef CODEGEN_HPP    
#define CODEGEN_HPP

#include "asm_node.hpp"
#include "asm_visitor.hpp"
#include <unordered_map>
#include "tac_node.hpp"

//forward declaration
class TAC_AST;

class ASM_AST {
    public:

    ASM_AST(TAC_AST &tree);

    ~ASM_AST();

    //generates asm from AST
    void asm_gen();

    std::unordered_map<asm_pseudo_reg*, int> get_pseudo_map();

    private:
    asm_program* root;
    int stack_offset;
    std::unordered_map<asm_pseudo_reg*, int> pseudo_map;
    
    void clean_map();

    asm_program* gen(tac_program* node);
    asm_function* gen(tac_function* node);
    void gen(tac_return* node, std::vector <asm_instruction*> &instructions);
    void gen(tac_unary* node, std::vector <asm_instruction*> &instructions);
    asm_operand* gen(tac_constant* node);
    asm_operand* gen(tac_var* node);

    friend class tac_return;
    friend class tac_unary;
    friend class tac_constant;
    friend class tac_var;
};

#endif