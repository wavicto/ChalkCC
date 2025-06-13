#ifndef TAC_VISITOR_HPP
#define TAC_VISITOR_HPP

//Forward declaration
class TacProgram;
class TacFunction;
class TacInstruction;
class TacReturn;
class TacUnary;
class TacBinary;
class TacVal;
class TacConstant;
class TacVar;

class TacVisitor {
    public:
    virtual void visit(TacProgram* node) = 0;
    virtual void visit(TacFunction* node) = 0;
    virtual void visit(TacReturn* node) = 0;
    virtual void visit(TacUnary* node) = 0;
    virtual void visit(TacBinary* node) = 0;
    virtual void visit(TacConstant* node) = 0;
    virtual void visit(TacVar* node) = 0;

    virtual ~TacVisitor(){}
};

#endif