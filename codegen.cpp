#include "codegen.hpp"

ASM_AST::ASM_AST(AST &tree)
{
    Generator g;
    root = g.gen(tree.get_root());
}

ASM_AST::~ASM_AST(){
    Cleaner worker;
    worker.visit(this->root);
}