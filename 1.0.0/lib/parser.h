#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "ast.h"
#include "scope.h"


typedef struct PARSER_STRUCT
{
    Lexer* lexer;
    Token* current_token;
    Token* prev_token;
    Scope* scope;
} Parser;

Parser* init_parser(Lexer* lexer);

void eat(Parser* parser, int tokenype);

AST* parse(Parser* parser, Scope* scope);

AST* parse_statement(Parser* parser, Scope* scope);

AST* parse_statements(Parser* parser, Scope* scope);

AST* parse_expr(Parser* parser, Scope* scope);

AST* parse_factor(Parser* parser, Scope* scope);

AST* parse_term(Parser* parser, Scope* scope);

AST* parse_fun(Parser* parser, Scope* scope);
        
AST* parse_vardef(Parser* parser, Scope* scope);

AST* parse_fundef(Parser* parser, Scope* scope);

AST* parse_variable(Parser* parser, Scope* scope);

AST* parse_str(Parser* parser, Scope* scope);

AST* parse_id(Parser* parser, Scope* scope);
#endif
