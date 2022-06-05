#ifndef SCOPE_H
#define SCOPE_H
#include "ast.h"

typedef struct SCOPE_STRUCT {
    Ast** fundefs;
    size_t fundefs_size;
    Ast** vardefs;
    size_t vardefs_size;
} Scope;

Scope* init_scope();
Ast* add_fundef(Scope* scope, Ast* fundef);
Ast* get_fundef(Scope* scope, const char* fun_name);
Ast* add_vardef(Scope* scope, Ast* vardef);
Ast* get_vardef(Scope* scope, const char* var_name);

#endif