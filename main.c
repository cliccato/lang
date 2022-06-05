#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "lib/lexer.h"
#include "lib/parser.h"
#include "lib/visitor.h"
#include "lib/io.h"
#define EXT ".hello"
#define LIMIT 50

void help() {
    printf("<mc> per aprire la shell\n");
    printf("<mc> <files> per eseguire i file\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    int i;

    if (argc >= 2){
        for(i = 1; i < argc; i++){
            int len = strlen(argv[i]);
            char* extension = &argv[i][len-6];
            if(strcmp(extension, EXT) == 0) {
                Lexer* lexer = init_lexer(file_contents(argv[i]));
                Parser* parser = init_parser(lexer);
                Ast* root = parse(parser, parser->scope);
                Visitor* visitor = init_visitor();
                Ast* d = visit(visitor, root);
            }

            else {
                help();
            }
        }
    } else {
        char input[LIMIT];
        while(1){
            printf("Shell $ ");
            fgets(input, LIMIT, stdin);
            Lexer* lexer = init_lexer(input);
            Parser* parser = init_parser(lexer);
            Ast* root = parse(parser, parser->scope);
            Visitor* visitor = init_visitor();
            visit(visitor, root);
        }
    }

    return 0;
}

