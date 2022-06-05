#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/lexer.h"
#include "lib/parser.h"
//#include "lib/visitor.h"
//#include "lib/io.h"
#define EXT ".mc"
#define LIMIT 50

void help() {
    printf("da fare dopo\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    int i;

    if (argc >= 2){
        for(i = 1; i < argc; i++){
            int len = strlen(argv[i]);
            char* extension = &argv[i][len-strlen(EXT)];
            if(strcmp(extension, EXT) == 0) {
                //printf("Estensione verificata");
                Lexer* lexer = init_lexer(get_file_contents(argv[i]));
                Parser* parser = init_parser(lexer);
                Ast* root = parse(parser, parser->scope);
                //Visitor* visitor = init_visitor();
                //visit(visitor, root);
            }

            else {
                help();
            }
        }
    }
    else {
        char input[LIMIT];
        while(1){
            printf("Shell $ ");
            fgets(input, LIMIT, stdin);
            Lexer* lexer = init_lexer(input);
            //parser_T* parser = init_parser(lexer);
            //AST_T* root = parser_parse(parser, parser->scope);
            //visitor_T* visitor = init_visitor();
            //visitor_visit(visitor, root);
        }
    }

    return 0;
}

