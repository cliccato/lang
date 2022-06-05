#include "lib/ast.h"


AST* init_ast(int type)
{
    AST* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    ast->scope = (void*) 0;

    /* AST_VARDEF */
    ast->vardef_name = (void*) 0;
    ast->vardef_value = (void*) 0;

    /* AST_FUNDEF */
    ast->fundef_body = (void*) 0;
    ast->fundef_name = (void*) 0;
    ast->fundef_args = (void*) 0;
    ast->fundef_args_size = 0;

    /* AST_VARIABLE */
    ast->name = (void*) 0;

    /* AST_FUN */
    ast->fun_name = (void*) 0;
    ast->fun_args = (void*) 0;
    ast->fun_args_size = 0;

    /* AST_STR */
    ast->str_value = (void*) 0;

    /* AST_COMP */
    ast->compound_value = (void*) 0;
    ast->compound_size = 0;

    return ast;
}
