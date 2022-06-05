#include "lib/scope.h"
#include <string.h>


Scope* init_scope()
{
    Scope* scope = calloc(1, sizeof(struct SCOPE_STRUCT));

    scope->fundefs = (void*) 0;
    scope->fundefs_size = 0;

    scope->vardefs = (void*) 0;
    scope->vardefs_size = 0;

    return scope;
}

AST* add_fundef(Scope* scope, AST* fdef)
{
    scope->fundefs_size += 1;

    if (scope->fundefs == (void*)0)
    {
        scope->fundefs = calloc(1, sizeof(struct AST_STRUCT*));
    }
    else
    {
        scope->fundefs =
            realloc(
                scope->fundefs,
                scope->fundefs_size * sizeof(struct AST_STRUCT**)
            );
    }

    scope->fundefs[scope->fundefs_size-1] =
        fdef;

    return fdef;
}

AST* get_fundef(Scope* scope, const char* fname)
{
    for (int i = 0; i < scope->fundefs_size; i++)
    {
        AST* fdef = scope->fundefs[i];

        if (strcmp(fdef->fundef_name, fname) == 0)
        {
            return fdef;
        }
    }

    return (void*)0;
}

AST* add_vardef(Scope* scope, AST* vdef)
{
    if (scope->vardefs == (void*) 0)
    {
        scope->vardefs = calloc(1, sizeof(struct AST_STRUCT*));
        scope->vardefs[0] = vdef;
        scope->vardefs_size += 1;
    }
    else
    {
        scope->vardefs_size += 1;
        scope->vardefs = realloc(
            scope->vardefs,
            scope->vardefs_size * sizeof(struct AST_STRUCT*)  
        );
        scope->vardefs[scope->vardefs_size-1] = vdef;
    }

    return vdef;
}

AST* get_vardef(Scope* scope, const char* name)
{
    for (int i = 0; i < scope->vardefs_size; i++)
    {
        AST* vdef = scope->vardefs[i];

        if (strcmp(vdef->vardef_name, name) == 0)
        {
            return vdef;
        }
    }

    return (void*)0;
}
