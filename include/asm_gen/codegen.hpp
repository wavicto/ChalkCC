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
class TacAST;

class AsmAST {
    public:

    //Initalizes AsmAST from TacAST
    AsmAST(TacAST &tree);

    ~AsmAST();

    //Generates assembly from AsmAST
    void asm_gen();

    //Returns: map of pseudo registers with their respective stack_offset
    //Helper method for second compiler pass that allocates stack locations for pseudo registers
    std::unordered_map<AsmPseudoReg*, int> get_pseudo_map();

    private:
    AsmProgram* root;
    int stack_offset;
    std::unordered_map<AsmPseudoReg*, int> pseudo_map;
    
    //Cleans up pseudo registers after they are replaced by a stack location
    void clean_map();

    //Helper functions that generates AsmAST by traversing through TacAST
    AsmProgram* gen(TacProgram* node);
    AsmFunction* gen(TacFunction* node);
    void gen(TacReturn* node, std::vector <AsmInstruction*> &instructions);
    void gen(TacUnary* node, std::vector <AsmInstruction*> &instructions);
    void gen(TacBinary* node, std::vector <AsmInstruction*> &instructions);
    AsmOperand* gen(TacConstant* node);
    AsmOperand* gen(TacVar* node);

    //Asists with AsmAST generation
    friend class TacReturn;
    friend class TacUnary;
    friend class TacConstant;
    friend class TacBinary;
    friend class TacVar;
};

#endif