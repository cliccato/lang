#include "lib/ast.h"

Ast* init_ast(int type) {
    Ast* ast = calloc(1, sizeof(struct AST_STRUCT));

    ast->type = type;
    ast->scope = (void*) 0;

    //variable def
    ast->vardef_val = (void*) 0;
    ast->vardef_name = (void*) 0;

    //variable
    ast->var_name = (void*) 0;

    //string
    ast->str_val = (void*) 0;

    //compound
    ast->comp_val = (void*) 0;
    ast->comp_size = 0;

    //function def
    ast->fundef_body = (void*) 0;
    ast->fundef_args = (void*) 0;
    ast->fundef_name = (void*) 0;
    ast->fundef_args_size = 0;

    //function
    ast->fun_args = (void*) 0;
    ast->fun_name = (void*) 0;
    ast->fun_args_size = 0;

    return ast;
}