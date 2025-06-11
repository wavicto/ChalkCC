#ifndef CODEGEN_HPP    
#define CODEGEN_HPP

#include <unordered_map>
#include "asm_gen/asm_node.hpp"
#include "asm_gen/asm_visitors/asm_pseudo_locator.hpp"
#include "asm_gen/asm_visitors/asm_instruction_finalizer.hpp"
#include "asm_gen/asm_visitors/asm_generator.hpp"
#include "asm_gen/asm_visitors/asm_cleaner.hpp"
#include "ir_gen/tac_node.hpp"

//Forward declaration
class TAC_AST;

class ASM_AST {
    public:

    //Initalizes ASM_AST from TAC_AST
    ASM_AST(TAC_AST &tree);

    ~ASM_AST();

    //Generates assembly from ASM_AST
    void asm_gen();

    //Returns: map of pseudo registers with their respective stack_offset
    //Helper method for second compiler pass that allocates stack locations for pseudo registers
    std::unordered_map<asm_pseudo_reg*, int> get_pseudo_map();

    private:
    asm_program* root;
    int stack_offset;
    std::unordered_map<asm_pseudo_reg*, int> pseudo_map;
    
    //Cleans up pseudo registers after they are replaced by a stack location
    void clean_map();

    //Helper functions that generates ASM_AST by traversing through TAC_AST
    asm_program* gen(tac_program* node);
    asm_function* gen(tac_function* node);
    void gen(tac_return* node, std::vector <asm_instruction*> &instructions);
    void gen(tac_unary* node, std::vector <asm_instruction*> &instructions);
    asm_operand* gen(tac_constant* node);
    asm_operand* gen(tac_var* node);

    //Asists with ASM_AST generatoin
    friend class tac_return;
    friend class tac_unary;
    friend class tac_constant;
    friend class tac_var;
};

#endif