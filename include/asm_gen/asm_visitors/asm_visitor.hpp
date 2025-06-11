#ifndef ASM_VISITOR_HPP    
#define ASM_VISITOR_HPP

//Forward declaration
class AsmProgram;
class AsmFunction;
class AsmInstruction;
class AsmMov;
class AsmRet;
class AsmUnary;
class StackAllocate;
class AsmOperand;
class AsmReg;
class AsmImm;
class AsmPseudoReg;
class StackLocation;

class AsmVisitor {
    public:
    virtual void visit(AsmProgram* node) = 0;
    virtual void visit(AsmFunction* node) = 0;
    virtual void visit(AsmMov* node) = 0;
    virtual void visit(AsmRet* node) = 0;
    virtual void visit(AsmUnary* node) = 0;
    virtual void visit(StackAllocate* node) = 0;
    virtual void visit(AsmReg* node) = 0;
    virtual void visit(AsmImm* node) = 0;
    virtual void visit(AsmPseudoReg* node) = 0;
    virtual void visit(StackLocation* node) = 0;
    virtual ~AsmVisitor(){}
};

#endif