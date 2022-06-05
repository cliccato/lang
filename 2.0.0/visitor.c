#include <stdio.h>
#include <string.h>
#include "lib/visitor.h"
#include "lib/scope.h"

static Ast* v_print(Visitor* visitor, Ast** args, int args_size) {
    int i;

    for (i = 0; i < args_size; i++) {
        Ast* visited = visit(visitor, args[i]);

        switch (visited->type) {
            case AST_STR: printf("%s\n", visited->str_val);
                break;
            default: printf("%p\n", visited);
                break;
        }
    }

    return init_ast(AST_NOOP);
}

static Ast* v_exit(Visitor* visitor, Ast** args, int args_size) {
    int i;

    for (i = 0; i < args_size; i++) {
        Ast* visited = visit(visitor, args[i]);

        switch (visited->type) {
            case AST_NOOP: printf("Test");
                exit(0);
                break;
            default: printf("%p\n", visited);
                break;
        }
    }

    return init_ast(AST_NOOP);
}

static Ast* v_clear(Visitor* visitor, Ast** args, int args_size) {
    int i;

    for (i = 0; i < args_size; i++) {
        Ast* visited = visit(visitor, args[i]);

        switch (visited->type) {
            case AST_NOOP: system("cls");
                break;
            default: printf("%p\n", visited);
                break;
        }
    }

    return init_ast(AST_NOOP);
}

Visitor* init_visitor() {
    Visitor* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    return visitor;
}

Ast* visit(Visitor* visitor, Ast* node) {
    switch (node->type) {
        case AST_VARDEF:
            return visit_vardef(visitor, node);
            break;
        case AST_FUNDEF:
            return visit_fundef(visitor, node);
            break;
        case AST_VAR:
            return visit_var(visitor, node);
            break;
        case AST_FUN:
            return visit_fun(visitor, node);
            break;
        case AST_STR:
            return visit_str(visitor, node);
            break;
        case AST_COMP:
            return visit_comp(visitor, node);
            break;
        case AST_NOOP:  
            return node;
            break;
    }

    printf("Tipo `%d` inesistente\n", node->type);
    //exit(1);

    return init_ast(AST_NOOP);
}

Ast* visit_vardef(Visitor* visitor, Ast* node) {
    add_vardef( node->scope, node);
    return node;
}

Ast* visit_fundef(Visitor* visitor, Ast* node) {
    add_fundef( node->scope, node);
    return node;
}

Ast* visit_var(Visitor* visitor, Ast* node) {
    Ast* vardef = get_vardef(node->scope, node->var_name);
    
    if (vardef != (void*) 0) {
        return visit(visitor, vardef->vardef_val);
    }

    printf("Variabile `%s` indefinita\n", node->var_name);
    exit(1);
}

Ast* visit_fun(Visitor* visitor, Ast* node) {
    int i;

    //funzioni di base
    if (strcmp(node->fun_name, "print") == 0) {
        return v_print(visitor, node->fun_args, node->fun_args_size);
    }
    if (strcmp(node->fun_name, "esc") == 0) {
        return v_exit(visitor, node->fun_args, node->fun_args_size);
    }
    if (strcmp(node->fun_name, "cls") == 0) {
        return v_clear(visitor, node->fun_args, node->fun_args_size);
    }

    Ast* fundef = get_fundef(node->scope, node->fun_name);

    if (fundef == (void*)0) {
        printf("Funzione `%s` non definita\n", node->fun_name);
        exit(1);
    }

    for (i = 0; i < (int) node->fun_args_size; i++) {
        Ast* var = (Ast*) fundef->fundef_args[i];
        Ast* value = (Ast*) node->fun_args[i];
        Ast* vardef = init_ast(AST_VARDEF);
        vardef->vardef_val = value;
        vardef->vardef_name = (char*) calloc(strlen(var->var_name) + 1, sizeof(char));
        strcpy(vardef->vardef_name, var->var_name);
        add_vardef(fundef->fundef_body->scope, vardef);
    }
    
    return visit(visitor, fundef->fundef_body);
}

Ast* visit_comp(Visitor* visitor, Ast* node) {
    int i;

    for (i = 0; i < node->comp_size; i++) {
        visit(visitor, node->comp_val[i]);
    }

    return init_ast(AST_NOOP);
}

Ast* visit_str(Visitor* visitor, Ast* node) {
    return node;
}