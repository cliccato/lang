#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "ast.h"
#include "scope.h"

typedef struct PARSER_STRUCT
{
    Lexer* lexer;
    Token* current_token;
    Token* previous_token;
    Scope* scope;
} Parser;

Parser* init_parser(Lexer* lexer);
void eat(Parser* parser, int type);
Ast* parse(Parser* parser, Scope* scope);
Ast* parse_statement(Parser* parser, Scope* scope);
Ast* parse_statements(Parser* parser, Scope* scope);
Ast* parse_expr(Parser* parser, Scope* scope);
Ast* parse_factor(Parser* parser, Scope* scope);
Ast* parse_term(Parser* parser, Scope* scope);
Ast* parse_fun(Parser* parser, Scope* scope);    
Ast* parse_vardef(Parser* parser, Scope* scope);
Ast* parse_fundef(Parser* parser, Scope* scope);
Ast* parse_var(Parser* parser, Scope* scope);
Ast* parse_str(Parser* parser, Scope* scope);
Ast* parse_id(Parser* parser, Scope* scope);

#endif