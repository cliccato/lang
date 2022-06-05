#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT {
    enum {
        AST_VARDEF,
        AST_FUNDEF,
        AST_VAR,
        AST_FUN,
        AST_STR,
        AST_COMP,
        AST_NOOP
    } type;

    struct SCOPE_STRUCT* scope;

    //variable def
    struct AST_STRUCT* vardef_val;

    char* vardef_name;

    //variable
    char* var_name;

    //string
    char* str_val;

    //compound
    struct AST_STRUCT** comp_val;

    size_t comp_size;

    //function def
    struct AST_STRUCT* fundef_body;
    struct AST_STRUCT** fundef_args;

    char* fundef_name;
    size_t fundef_args_size;

    //function
    struct AST_STRUCT** fun_args;

    char* fun_name;
    size_t fun_args_size;

} Ast;

Ast* init_ast(int type);

#endif