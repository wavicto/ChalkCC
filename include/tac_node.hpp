#ifndef TAC_NODE_HPP    
#define TAC_NODE_HPP

#include <string>
#include <vector>
#include "token.hpp"
#include "tac_visitor.hpp"

class TACNode {
    public:
    virtual void accept(tac_visitor* v) = 0;
    virtual ~TACNode(){}
};

class tac_program : public TACNode {
    public:
    virtual void accept(tac_visitor* v) override;

    tac_function* ptr;
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
};

class tac_return : public tac_instruction {
    public:
    virtual void accept(tac_visitor* v) override;

    tac_val* ptr;
};

class tac_unary : public tac_instruction {
    public:
    virtual void accept(tac_visitor* v) override;

    TokenType op;
    tac_val* src;
    tac_val* dst;
};

class tac_val : public TACNode {
    public:
    virtual void accept(tac_visitor* v) = 0;
};

class tac_constant : public tac_val {
    public:
    virtual void accept(tac_visitor* v) override;

    int value;
};

class tac_var : public tac_val {
    public:
    virtual void accept(tac_visitor* v) override;

    std::string name;
};

#endif