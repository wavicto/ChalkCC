#include "visitor.hpp"

Visitor::~Visitor() {}

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

void asm_program::accept(Visitor* v){
    v->visit(this);
}

void asm_function::accept(Visitor* v){
    v->visit(this);
}

void asm_instruction::accept(Visitor* v){
    v->visit(this);
}

void asm_mov::accept(Visitor* v){
    v->visit(this);
}

void asm_ret::accept(Visitor* v){
    v->visit(this);
}

void asm_operand::accept(Visitor* v){
    v->visit(this);
}

void asm_reg::accept(Visitor* v){
    v->visit(this);
}

void asm_imm::accept(Visitor* v){
    v->visit(this);
}

void Cleaner::visit(program* node){
    function* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(function* node){
    statement* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(statement* node){
    expression* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(expression* node){
    constant* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(constant* node){
    delete node;
}

void Cleaner::visit(asm_program* node){
    asm_function* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(asm_function* node){
    for (auto ptr : node->instructions){
        if (ptr){
            ptr->accept(this);
        }
    }
    delete node;
}

void Cleaner::visit(asm_instruction* node){
    asm_instruction* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(asm_mov* node){
    asm_operand* src = node->src;
    asm_operand* dst = node->dst;
    if (src){
        src->accept(this);
    }
    if (dst){
        src->accept(this);
    }
    delete node;
}

void Cleaner::visit(asm_ret* node){
    delete node;
}

void Cleaner::visit(asm_operand* node){
    asm_operand* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(asm_operand* node){
    asm_operand* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
    delete node;
}

void Cleaner::visit(asm_reg* node){
    delete node;
}

void Cleaner::visit(asm_imm* node){
    delete node;
}

void Traveler::visit(program* node){
    std::cout << "Program: " << std::endl;
    function* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void Traveler::visit(function* node){
    std::cout << "Function: Name: " << node->name << std::endl;
    statement* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void Traveler::visit(statement* node){
    std::cout << "Statement: Return: " << std::endl;
    expression* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void Traveler::visit(expression* node){
    std::cout << "Expression" << std::endl;
    constant* ptr = node->ptr;
    if (ptr){
        ptr->accept(this);
    }
}

void Traveler::visit(constant* node){
    std::cout << "Constant(" << node->value << ")" << std::endl;
}

asm_program* Generator::gen(program* node){
    asm_program* root = new asm_program;
    function* ptr = node->ptr;
    if (ptr){
        root->ptr = gen(ptr);
    }
    return root;
}

asm_function* Generator::gen(function* node){
    asm_function* func = new asm_function;
    statement* state = node->ptr;

    if(state){
        expression* exp = state->ptr;
        if (exp){
            func->instructions.push_back(gen(exp));
        }
        func->instructions.push_back(gen(state));
    }
    func->name = node->name;
    return func;
}

asm_instruction* Generator::gen(statement* node){
    asm_instruction* ptr = new asm_instruction;
    ptr->ptr = new asm_ret;
    return ptr;
}

asm_instruction* Generator::gen(expression* node){
    asm_instruction* ptr = new asm_instruction;
    asm_mov* mov = new asm_mov;

    ptr->ptr = mov;

    asm_operand* src = new asm_operand;
    asm_operand* dst = new asm_operand;

    mov->src = src;
    mov->dst = dst;

    asm_imm* v = new asm_imm;
    v->value = node->ptr->value;
    asm_reg* r = new asm_reg;
    r->name = EAX;

    src->ptr = v;
    dst->ptr = r;

    return ptr;

}
