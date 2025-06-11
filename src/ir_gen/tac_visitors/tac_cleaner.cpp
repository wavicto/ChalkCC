#include "ir_gen/tac_visitors/tac_cleaner.hpp"
#include "ir_gen/tac_node.hpp"

void tac_cleaner::visit(tac_program* node){
    tac_function* ptr = node->func_ptr;
    if(ptr){
        ptr->accept(this);
    }
    delete node;
}

void tac_cleaner::visit(tac_function* node){
    for (auto ptr : node->body){
        if (ptr){
            ptr->accept(this);
        }
    }
    delete node;
}

void tac_cleaner::visit(tac_return* node){
    delete node;
}

void tac_cleaner::visit(tac_unary* node){
    tac_val* src = node->src;
    tac_val* dst = node->dst;

    if (src){
        src->accept(this);
    }
    if (dst ){
        dst->accept(this);
    }
    delete node;
}

void tac_cleaner::visit(tac_constant* node){
    delete node;
}

void tac_cleaner::visit(tac_var* node){}