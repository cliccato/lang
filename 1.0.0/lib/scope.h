#ifndef SCOPE_H
#define SCOPE_H
#include "ast.h"

typedef struct SCOPE_STRUCT
{
    AST** fundefs;
    size_t fundefs_size;

    AST** vardefs;
    size_t vardefs_size;
} Scope;

Scope* init_scope();

AST* add_fundef(Scope* scope, AST* fdef);

AST* get_fundef(Scope* scope, const char* fname);

AST* add_vardef(Scope* scope, AST* vdef);

AST* get_vardef(Scope* scope, const char* name);
#endif
