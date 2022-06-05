#include "lib/visitor.h"
#include "lib/scope.h"
#include <stdio.h>
#include <string.h>
#define BUFFER 50

char stdin_buffer[BUFFER];

static AST* builtin_function_print(Visitor* visitor, AST** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        AST* visited_ast = visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_STR: printf("%s\n", visited_ast->str_value); break;
        }
    }

    return init_ast(AST_NOOP);
}

static AST* builtin_function_shell()
{
    int buf = 0;
    char cmd[50];
    char c;
 
        do {
            c=getchar();
            cmd[buf] = c;
            buf++;
        } while(c != '\n' || buf == BUFFER-1);

        cmd[buf] = '\0';

        system(cmd);


    return init_ast(AST_NOOP);
}

static AST* builtin_function_write_buffer()
{
    int buf = 0;
    char c;
 
    do {
        c=getchar();
        stdin_buffer[buf] = c;
        buf++;
    } while(c != '\n' || buf == BUFFER-1);

    stdin_buffer[buf] = '\0';

    return init_ast(AST_NOOP);
}

static AST* builtin_function_read_buffer()
{
    printf("%s", stdin_buffer);

    return init_ast(AST_NOOP);
}

static AST* builtin_function_pause()
{
    char c;
    do {
        c = getch();
    } while(c != '\n');

    return init_ast(AST_NOOP);
}

static AST* builtin_function_comment(Visitor* visitor, AST** args, int args_size)
{
    return init_ast(AST_NOOP);
}

static AST* builtin_function_exit(Visitor* visitor, AST** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        AST* visited_ast = visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_NOOP: exit(0); break;
        }
    }

    return init_ast(AST_NOOP);
}

static AST* builtin_function_clear(Visitor* visitor, AST** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        AST* visited_ast = visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_NOOP: system("cls"); break;
        }
    }

    return init_ast(AST_NOOP);
}

Visitor* init_visitor()
{
    Visitor* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));

    return visitor;
}

AST* visit(Visitor* visitor, AST* node)
{
    switch (node->type)
    {
        case AST_VARDEF: return visit_vardef(visitor, node); break;
        case AST_FUNDEF: return visit_fundef(visitor, node); break;
        case AST_VARIABLE: return visit_variable(visitor, node); break;
        case AST_FUN: return visit_fun(visitor, node); break;
        case AST_STR: return visit_str(visitor, node); break;
        case AST_COMP: return visit_compound(visitor, node); break;
        case AST_NOOP: return node; break;
    }

    printf("Tipo `%d` indefinito\n", node->type);
    exit(1);

    return init_ast(AST_NOOP);
}

AST* visit_vardef(Visitor* visitor, AST* node)
{
    add_vardef(
        node->scope,
        node        
    ); 

    return node;
}

AST* visit_fundef(Visitor* visitor, AST* node)
{
    add_fundef(
        node->scope,
        node        
    );

    return node;
}

AST* visit_variable(Visitor* visitor, AST* node)
{
    AST* vdef = get_vardef(
        node->scope,
        node->name
    );
    
    if (vdef != (void*) 0)
        return visit(visitor, vdef->vardef_value);

    printf("Variabile `%s` non definita\n", node->name);
    exit(1);
}

AST* visit_fun(Visitor* visitor, AST* node)
{
    if (strcmp(node->fun_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->fun_args, node->fun_args_size);
    }

    if (strcmp(node->fun_name, "exit") == 0)
    {
        return builtin_function_exit(visitor, node->fun_args, node->fun_args_size);
    }

    if (strcmp(node->fun_name, "clear") == 0)
    {
        return builtin_function_clear(visitor, node->fun_args, node->fun_args_size);
    }
    if (strcmp(node->fun_name, "exec") == 0)
    {
        return builtin_function_shell();
    }
    if (strcmp(node->fun_name, "write") == 0)
    {
        return builtin_function_write_buffer();
    }
    if (strcmp(node->fun_name, "read") == 0)
    {
        return builtin_function_read_buffer();
    }/*
    if (strcmp(node->fun_name, "pause") == 0)
    {
        return builtin_function_pause();
    }*/
    if (strcmp(node->fun_name, "comment") == 0)
    {
        return builtin_function_comment(visitor, node->fun_args, node->fun_args_size);
    }


    AST* fdef = get_fundef(
        node->scope,
        node->fun_name
    );

    if (fdef == (void*)0)
    {
        printf("Metodo `%s` indefinito\n", node->fun_name);
        exit(1);
    }

    for (int i = 0; i < (int) node->fun_args_size; i++)
    {
        AST* ast_var = (AST*) fdef->fun_args[i];
        AST* ast_value = (AST*) node->fun_args[i];
        AST* ast_vardef = init_ast(AST_VARDEF);
        ast_vardef->vardef_value = ast_value;
        ast_vardef->vardef_name = (char*) calloc(strlen(ast_var->name) + 1, sizeof(char));
        strcpy(ast_vardef->vardef_name, ast_var->name);
        add_vardef(fdef->fundef_body->scope, ast_vardef);
    }
    
    return visit(visitor, fdef->fundef_body);
}

AST* visit_str(Visitor* visitor, AST* node)
{
    return node;
}

AST* visit_compound(Visitor* visitor, AST* node)
{
    for (int i = 0; i < node->compound_size; i++)
    {
        visit(visitor, node->compound_value[i]);
    }

    return init_ast(AST_NOOP);
}
