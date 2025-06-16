#ifndef CODEGEN_HPP    
#define CODEGEN_HPP

#include <unordered_map>
#include "asm_gen/asm_node.hpp"
#include "asm_gen/asm_visitors/asm_pseudo_locator.hpp"
#include "asm_gen/asm_visitors/asm_instruction_finalizer.hpp"
#include "asm_gen/asm_visitors/asm_generator.hpp"
#include "ir_gen/tac_node.hpp"

//Forward declaration
class TacAST;

class AsmAST {
    public:

    //Initalizes AsmAST from TacAST
    AsmAST(TacAST &tree);

    //Generates assembly from AsmAST
    void asm_gen();

    //Returns: map of pseudo registers with their respective stack_offset
    //Helper method for second compiler pass that allocates stack locations for pseudo registers
    std::unordered_map<std::shared_ptr<AsmPseudoReg>, int> get_pseudo_map();

    private:
    std::unique_ptr<AsmProgram> root;
    int stack_offset;
    std::unordered_map<std::shared_ptr<AsmPseudoReg>, int> pseudo_map;

    //Helper functions that generates AsmAST by traversing through TacAST
    std::unique_ptr<AsmProgram> gen(TacProgram* node);
    std::unique_ptr<AsmFunction> gen(TacFunction* node);
    void gen(TacReturn* node, std::vector<std::unique_ptr<AsmInstruction>> &instructions);
    void gen(TacUnary* node, std::vector<std::unique_ptr<AsmInstruction>> &instructions);
    void gen(TacBinary* node, std::vector<std::unique_ptr<AsmInstruction>> &instructions);
    std::shared_ptr<AsmImm> gen(TacConstant* node);
    std::shared_ptr<AsmPseudoReg> gen(TacVar* node);

    //Asists with AsmAST generation
    friend class TacReturn;
    friend class TacUnary;
    friend class TacConstant;
    friend class TacBinary;
    friend class TacVar;
};

#endif