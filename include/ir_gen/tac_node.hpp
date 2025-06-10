#ifndef TAC_NODE_HPP    
#define TAC_NODE_HPP

#include <string>
#include <vector>
#include "lexical_analysis/token.hpp"
#include "ir_gen/tac_visitor.hpp"
#include "asm_gen/asm_node.hpp"
#include "asm_gen/codegen.hpp"

//Forward declaration
class ASM_AST;

class TACNode {
    public:
    virtual void accept(tac_visitor* v) = 0;
    virtual ~TACNode();
};

class tac_program : public TACNode {
    public:
    virtual void accept(tac_visitor* v) override;

    tac_function* func_ptr;
};

class tac_function : public TACNode {
    public:
    virtual void accept(tac_visitor* v) override;

    std::string id;
    std::vector<tac_instruction*> body;
};

class tac_instruction : public TACNode {
    public:
    virtual void accept(tac_visitor* v) = 0;
    //Asists ASM_AST generation through polymorphism on children classes
    virtual void gen(ASM_AST* tree, std::vector <asm_instruction*> &instructions) = 0;
};

class tac_return : public tac_instruction {
    public:
    virtual void accept(tac_visitor* v) override;
    virtual void gen(ASM_AST* tree, std::vector <asm_instruction*> &instructions) override;

    tac_val* val_ptr;
};

class tac_unary : public tac_instruction {
    public:
    virtual void accept(tac_visitor* v) override;
    virtual void gen(ASM_AST* tree, std::vector <asm_instruction*> &instructions) override;

    TokenType op;
    tac_val* src;
    //dst must be a var
    tac_val* dst;
};

class tac_val : public TACNode {
    public:
    virtual void accept(tac_visitor* v) = 0;
    //Asists ASM_AST generation through polymorphism on children classes
    virtual asm_operand* gen(ASM_AST* tree) = 0;
};

class tac_constant : public tac_val {
    public:
    virtual void accept(tac_visitor* v) override;
    virtual asm_operand* gen(ASM_AST* tree) override;

    int value;
};

class tac_var : public tac_val {
    public:
    virtual void accept(tac_visitor* v) override;
    virtual asm_operand* gen(ASM_AST* tree) override;

    std::string name;
};

#endif