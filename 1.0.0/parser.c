#include "lib/parser.h"
#include "lib/scope.h"
#include <stdio.h>
#include <string.h>


Parser* init_parser(Lexer* lexer)
{
    Parser* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = get_next_token(lexer);
    parser->prev_token = parser->current_token;

    parser->scope = init_scope();

    return parser;
}

void eat(Parser* parser, int tokenype)
{
    if (parser->current_token->type == tokenype)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = get_next_token(parser->lexer);
    }
    else
    {
        printf(
            "Token `%s` insapettato",
            parser->current_token->value
        );
        exit(1);
    }
}

AST* parse(Parser* parser, Scope* scope)
{
    return parse_statements(parser, scope);
}

AST* parse_statement(Parser* parser, Scope* scope)
{
    switch (parser->current_token->type)
    {
        case TOKEN_ID: return parse_id(parser, scope);
    }

    return init_ast(AST_NOOP);
}

AST* parse_statements(Parser* parser, Scope* scope)
{
    AST* compound = init_ast(AST_COMP);
    compound->scope = scope;
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST* ast_statement = parse_statement(parser, scope);
    ast_statement->scope = scope;
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;

    while (parser->current_token->type == TOKEN_SEMICOLON)
    {
        eat(parser, TOKEN_SEMICOLON);

        AST* ast_statement = parse_statement(parser, scope);

        if (ast_statement)
        {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size * sizeof(struct AST_STRUCT*)
            );
            compound->compound_value[compound->compound_size-1] = ast_statement;
        }
    }

    return compound;
}

AST* parse_expr(Parser* parser, Scope* scope)
{
    switch (parser->current_token->type)
    {
        case TOKEN_STR: return parse_str(parser, scope);
        case TOKEN_ID: return parse_id(parser, scope);
    }

    return init_ast(AST_NOOP);
}

AST* parse_factor(Parser* parser, Scope* scope)
{
}

AST* parse_term(Parser* parser, Scope* scope)
{
}

AST* parse_fun(Parser* parser, Scope* scope)
{
    AST* fun = init_ast(AST_FUN);

    fun->fun_name = parser->prev_token->value;
    eat(parser, TOKEN_LTONDA); 

    fun->fun_args = calloc(1, sizeof(struct AST_STRUCT*));

    AST* ast_expr = parse_expr(parser, scope);
    fun->fun_args[0] = ast_expr;
    fun->fun_args_size += 1;

    while (parser->current_token->type == TOKEN_VIGOLA)
    {
        eat(parser, TOKEN_VIGOLA);

        AST* ast_expr = parse_expr(parser, scope);
        fun->fun_args_size += 1;
        fun->fun_args = realloc(
            fun->fun_args,
            fun->fun_args_size * sizeof(struct AST_STRUCT*)
        );
        fun->fun_args[fun->fun_args_size-1] = ast_expr;
    }
    eat(parser, TOKEN_RTONDA);

    fun->scope = scope;

    return fun;
}

AST* parse_vardef(Parser* parser, Scope* scope)
{
    eat(parser, TOKEN_ID); // var
    char* vardef_name = parser->current_token->value;
    eat(parser, TOKEN_ID); // var name
    eat(parser, TOKEN_EQUAL);
    AST* vardef_value = parse_expr(parser, scope);

    AST* vardef = init_ast(AST_VARDEF);
    vardef->vardef_name = vardef_name;
    vardef->vardef_value = vardef_value;

    vardef->scope = scope;

    return vardef;
}

AST* parse_fundef(Parser* parser, Scope* scope)
{
    AST* ast = init_ast(AST_FUNDEF);
    eat(parser, TOKEN_ID);

    char* function_name = parser->current_token->value;
    ast->fundef_name = calloc(
            strlen(function_name) + 1, sizeof(char)
    );
    strcpy(ast->fundef_name, function_name);

    eat(parser, TOKEN_ID);

    eat(parser, TOKEN_LTONDA);

    ast->fun_args =
        calloc(1, sizeof(struct AST_STRUCT*));

    AST* arg = parse_variable(parser, scope);
    ast->fun_args_size += 1;
    ast->fun_args[ast->fun_args_size-1] = arg;

    while (parser->current_token->type == TOKEN_VIGOLA)
    {
        eat(parser, TOKEN_VIGOLA);

        ast->fun_args_size += 1;

        ast->fun_args =
            realloc(
                    ast->fun_args,
                    ast->fun_args_size * sizeof(struct AST_STRUCT*)
                   );

        AST* arg = parse_variable(parser, scope);
        ast->fun_args[ast->fun_args_size-1] = arg;
    }

    eat(parser, TOKEN_RTONDA);
    
    eat(parser, TOKEN_LGRAFFA);
    
    ast->fundef_body = parse_statements(parser, scope);

    eat(parser, TOKEN_RGRAFFA);

    ast->scope = scope;

    return ast;
}

AST* parse_variable(Parser* parser, Scope* scope)
{
    char* token_value = parser->current_token->value;
    eat(parser, TOKEN_ID);
    if (parser->current_token->type == TOKEN_LTONDA)
        return parse_fun(parser, scope);

    AST* var = init_ast(AST_VARIABLE);
    var->name = token_value;

    var->scope = scope;

    return var;
}

AST* parse_str(Parser* parser, Scope* scope)
{
    AST* str = init_ast(AST_STR);
    str->str_value = parser->current_token->value;

    eat(parser, TOKEN_STR);

    str->scope = scope;

    return str;
}

AST* parse_id(Parser* parser, Scope* scope)
{
    if (strcmp(parser->current_token->value, "var") == 0)
    {
        return parse_vardef(parser, scope);
    }
    else
    if (strcmp(parser->current_token->value, "func") == 0)
    {
        return parse_fundef(parser, scope);
    }
    else
    {
        return parse_variable(parser, scope);
    }
}
