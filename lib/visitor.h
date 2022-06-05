#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"

typedef struct VISITOR_STRUCT {

} Visitor;

Visitor* init_visitor();
Ast* visit(Visitor* visitor, Ast* node);
Ast* visit_vardef(Visitor* visitor, Ast* node);
Ast* visit_fundef(Visitor* visitor, Ast* node);
Ast* visit_var(Visitor* visitor, Ast* node);
Ast* visit_fun(Visitor* visitor, Ast* node);
Ast* visit_str(Visitor* visitor, Ast* node);
Ast* visit_comp(Visitor* visitor, Ast* node);

#endif