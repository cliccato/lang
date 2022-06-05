#include <stdio.h>
#include <string.h>
#include "lib/parser.h"
#include "lib/scope.h"

Parser* init_parser(Lexer* lexer) {
    Parser* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = get_token(lexer);
    parser->previous_token = parser->current_token;

    parser->scope = init_scope();

    return parser;
}

void eat(Parser* parser, int type) {
    if (parser->current_token->type == type) {
        parser->previous_token = parser->current_token;
        parser->current_token = get_token(parser->lexer);
    } else {
        printf("Errore: Token `%s` di tipo %d non aspettato", parser->current_token->value, parser->current_token->type);
        exit(1);
    }
}

Ast* parse(Parser* parser, Scope* scope) {
    Ast* statements = parse_statements(parser, scope);
    return statements;
}

Ast* parse_statement(Parser* parser, Scope* scope) {

    switch (parser->current_token->type)
    {
        case T_ID: return parse_id(parser, scope);
    }

    return init_ast(AST_NOOP);
}

Ast* parse_statements(Parser* parser, Scope* scope) {
    Ast* compound = init_ast(AST_COMP);

    compound->scope = scope;
    compound->comp_val = calloc(1, sizeof(struct AST_STRUCT*));
    Ast* statement = parse_statement(parser, scope);
    statement->scope = scope;
    compound->comp_val[0] = statement;
    compound->comp_size += 1;

    while (parser->current_token->type == T_SEMICOLON) {
        printf("%d", compound->type);
        eat(parser, T_SEMICOLON);
        printf("eatttt");
        Ast* statement = parse_statement(parser, scope);

        if (statement) {
            compound->comp_size += 1;
            compound->comp_val = realloc(compound->comp_val, compound->comp_size * sizeof(struct AST_STRUCT*));
            compound->comp_val[compound->comp_size-1] = statement;
        }
    }
    printf("test");
    return compound;
}

Ast* parse_expr(Parser* parser, Scope* scope) {
    switch (parser->current_token->type) {
        case T_STRING: return parse_str(parser, scope);
        case T_ID: return parse_id(parser, scope);
    }

    return init_ast(AST_NOOP);
}

Ast* parse_factor(Parser* parser, Scope* scope) {

}

Ast* parse_fun(Parser* parser, Scope* scope) {
    Ast* fun_call = init_ast(AST_FUN);

    fun_call->fun_name = parser->previous_token->value;
    eat(parser, T_LTONDA); 

    fun_call->fun_args = calloc(1, sizeof(struct AST_STRUCT*));

    Ast* ast_expr = parse_expr(parser, scope);
    fun_call->fun_args[0] = ast_expr;
    fun_call->fun_args_size += 1;

    while (parser->current_token->type == T_VIRGOLA)
    {
        eat(parser, T_VIRGOLA);

        Ast* ast_expr = parse_expr(parser, scope);
        fun_call->fun_args_size += 1;
        fun_call->fun_args = realloc(fun_call->fun_args, fun_call->fun_args_size * sizeof(struct AST_STRUCT*));
        fun_call->fun_args[fun_call->fun_args_size-1] = ast_expr;
    }

    eat(parser, T_RTONDA);
    fun_call->scope = scope;

    return fun_call;
}

Ast* parse_vardef(Parser* parser, Scope* scope) {
    eat(parser, T_ID);
    char* var_name = parser->current_token->value;

    eat(parser, T_ID);
    eat(parser, T_EQUAL);

    Ast* var_value = parse_expr(parser, scope);
    Ast* vardef = init_ast(AST_VARDEF);

    vardef->var_name = var_name;
    vardef->vardef_val = var_value;
    vardef->scope = scope;

    return vardef;
}

Ast* parse_fundef(Parser* parser, Scope* scope) {
    Ast* ast = init_ast(AST_FUNDEF);
    eat(parser, T_ID);

    char* function_name = parser->current_token->value;
    ast->fundef_name = calloc(strlen(function_name) + 1, sizeof(char));
    
    strcpy(ast->fundef_name, function_name);

    eat(parser, T_ID);
    eat(parser, T_LTONDA);

    ast->fundef_args = calloc(1, sizeof(struct AST_STRUCT*));

    Ast* arg = parse_var(parser, scope);
    ast->fundef_args_size += 1;
    ast->fundef_args[ast->fundef_args_size-1] = arg;

    while (parser->current_token->type == T_VIRGOLA) {
        eat(parser, T_VIRGOLA);

        ast->fundef_args_size += 1;
        ast->fundef_args = realloc(ast->fundef_args, ast->fundef_args_size * sizeof(struct AST_STRUCT*));

        Ast* arg = parse_var(parser, scope);
        ast->fundef_args[ast->fundef_args_size-1] = arg;
    }

    eat(parser, T_RTONDA);
    eat(parser, T_LGRAFFA);
    ast->fundef_body = parse_statements(parser, scope);
    eat(parser, T_RGRAFFA);
    ast->scope = scope;

    return ast;
}

Ast* parse_var(Parser* parser, Scope* scope) {
    char* value = parser->current_token->value;
    eat(parser, T_ID);

    if (parser->current_token->type == T_LTONDA) {
        return parse_fun(parser, scope);
    }

    Ast* var = init_ast(AST_VAR);
    var->var_name = value;

    var->scope = scope;

    return var;
}

Ast* parse_str(Parser* parser, Scope* scope) {
    Ast* string = init_ast(AST_STR);

    string->str_val = parser->current_token->value;
    eat(parser, T_STRING);
    string->scope = scope;

    return string;
}

Ast* parse_id(Parser* parser, Scope* scope) {
    if (strcmp(parser->current_token->value, "var") == 0) {
        return parse_vardef(parser, scope);
    }
    else
    if (strcmp(parser->current_token->value, "function") == 0) {
        return parse_fundef(parser, scope);
    }
    else {
        return parse_var(parser, scope);
    }
}


Ast* parse_term(Parser* parser, Scope* scope) {

}