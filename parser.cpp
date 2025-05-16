#include "parser.hpp"

void program::accept(Visitor* v){
    v->visit(this);
}

void function::accept(Visitor* v){
    v->visit(this);
}

void statement::accept(Visitor* v){
    v->visit(this);
}

void expression::accept(Visitor* v){
    v->visit(this);
}

void constant::accept(Visitor* v){
    v->visit(this);
}

void return_statement::accept(Visitor* v){
    v->visit(this);
}

void Cleaner::visit(program* node){
    function* ptr = node->ptr;
    if (ptr){
        visit(ptr);
    }
    delete node;
}

void Cleaner::visit(function* node){
    statement* ptr = node->ptr;
    if (ptr){
        visit(ptr);
    }
    delete node;
}

void Cleaner::visit(statement* node){
    return_statement* ptr = node->ptr;
    if (ptr){
        visit(ptr);
    }
    delete node;
}

void Cleaner::visit(return_statement* node){
    expression* ptr = node->ptr;
    if (ptr){
        visit(ptr);
    }    
    delete node;
}

void Cleaner::visit(expression* node){
    constant* ptr = node->ptr;
    if (ptr){
        visit(ptr);
    }
    delete node;
}

void Cleaner::visit(constant* node){
    delete node;
}

AST::~AST(){
    Cleaner worker;
    worker.visit(this->root);
}