#include "ir_gen/tac_visitors/tac_cleaner.hpp"
#include "ir_gen/tac_node.hpp"

void TacCleaner::visit(TacProgram* node){
    TacFunction* ptr = node->func_ptr;
    if(ptr){
        ptr->accept(this);
    }
    delete node;
}

void TacCleaner::visit(TacFunction* node){
    for (auto ptr : node->body){
        if (ptr){
            ptr->accept(this);
        }
    }
    delete node;
}

void TacCleaner::visit(TacReturn* node){
    if (node->val_ptr){
        (node->val_ptr)->accept(this);
    }
    delete node;
}

void TacCleaner::visit(TacUnary* node){
    TacVal* src = node->src;
    TacVal* dst = node->dst;

    if (src){
        src->accept(this);
    }
    if (dst ){
        dst->accept(this);
    }
    delete node;
}

void TacCleaner::visit(TacBinary* node){
    TacVal* src_1 = node->src_1;
    TacVal* src_2 = node->src_2;
    TacVal* dst = node->dst;

    if (src_1){
        src_1->accept(this);
    }
    if (src_2){
        src_2->accept(this);
    }
    if (dst ){
        dst->accept(this);
    }
    delete node;
}

void TacCleaner::visit(TacConstant* node){
    delete node;
}

//temp variables will be cleaned up in another method
void TacCleaner::visit(TacVar* node){}