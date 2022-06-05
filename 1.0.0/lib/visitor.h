#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"

typedef struct VISITOR_STRUCT
{
} Visitor;

Visitor* init_visitor();

AST* visit(Visitor* visitor, AST* node);

AST* visit_vardef(Visitor* visitor, AST* node);

AST* visit_fundef(Visitor* visitor, AST* node);

AST* visit_variable(Visitor* visitor, AST* node);

AST* visit_fun(Visitor* visitor, AST* node);

AST* visit_str(Visitor* visitor, AST* node);

AST* visit_compound(Visitor* visitor, AST* node);
#endif
