#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT
{
    enum {
        AST_VARDEF,
        AST_FUNDEF,
        AST_VARIABLE,
        AST_FUN,
        AST_STR,
        AST_COMP,
        AST_NOOP
    } type;

    struct SCOPE_STRUCT* scope;
    char* vardef_name;
    struct AST_STRUCT* vardef_value;
    struct AST_STRUCT* fundef_body;
    char* fundef_name;
    struct AST_STRUCT** fundef_args;
    size_t fundef_args_size;
    char* name;
    char* fun_name;
    struct AST_STRUCT** fun_args;
    size_t fun_args_size;
    char* str_value;
    struct AST_STRUCT** compound_value;
    size_t compound_size;
} AST;

AST* init_ast(int type);
#endif
