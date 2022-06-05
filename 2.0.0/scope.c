#include <string.h>
#include "lib/scope.h"

Scope* init_scope() {
    Scope* scope = calloc(1, sizeof(struct SCOPE_STRUCT));

    scope->fundefs = (void*) 0;
    scope->fundefs_size = 0;
    scope->vardefs = (void*) 0;
    scope->vardefs_size = 0;

    return scope;
}

Ast* add_fundef(Scope* scope, Ast* fundef) {
    scope->fundefs_size += 1;

    if (scope->fundefs == (void*)0) {
        scope->fundefs = calloc(1, sizeof(struct AST_STRUCT*));
    } else {
        scope->fundefs = realloc(scope->fundefs, scope->fundefs_size * sizeof(struct AST_STRUCT**));
    }

    scope->fundefs[scope->fundefs_size-1] = fundef;

    return fundef;
}

Ast* get_fundef(Scope* scope, const char* fun_name) {
    int i;

    for (i = 0; i < scope->fundefs_size; i++) {
        Ast* fundef = scope->fundefs[i];

        if (strcmp(fundef->fundef_name, fun_name) == 0) {
            return fundef;
        }
    }

    return (void*)0;
}

Ast* add_vardef(Scope* scope, Ast* vardef) {
    if (scope->vardefs == (void*) 0) {
        scope->vardefs = calloc(1, sizeof(struct AST_STRUCT*));
        scope->vardefs[0] = vardef;
        scope->vardefs_size += 1;
    } else {
        scope->vardefs_size += 1;
        scope->vardefs = realloc(scope->vardefs, scope->vardefs_size * sizeof(struct AST_STRUCT*));
        scope->vardefs[scope->vardefs_size-1] = vardef;
    }

    return vardef;
}

Ast* get_vardef(Scope* scope, const char* var_name) {
    int i;

    for (i = 0; i < scope->vardefs_size; i++) {
        Ast* vardef = scope->vardefs[i];

        if (strcmp(vardef->vardef_name, var_name) == 0) {
            return vardef;
        }
    }

    return (void*)0;
}
