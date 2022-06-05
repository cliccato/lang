#include <stdio.h>
#include <string.h>
#include "lib/lexer.h"
#include "lib/parser.h"
#include "lib/visitor.h"
#include "lib/io.h"

#define MAX_LIMIT 50
void print_help()
{
    printf("<mc> per aprire la shell\n");
    printf("<mc> <files> per eseguire i file\n");
    exit(1);
}

int main(int argc, char* argv[])
{
    if (argc >= 2){
        for(int i = 1; i < argc; i++){
            int len = strlen(argv[i]);
            char* last_four = &argv[i][len-3];
            if(strcmp(last_four,".mc") == 0){
                                Lexer* lexer = init_lexer(
                    file_contents(argv[i])
                );
                Parser* parser = init_parser(lexer);
                AST* root = parse(parser, parser->scope);
                Visitor* visitor = init_visitor();
                visit(visitor, root);
            }

            else {
                print_help();
            }
        }
    }
    else {
        char input[MAX_LIMIT];
        while(1){
            printf("Shell $ ");
            fgets(input,MAX_LIMIT, stdin);
            Lexer* lexer = init_lexer(input);
            Parser* parser = init_parser(lexer);
            AST* root = parse(parser, parser->scope);
            Visitor* visitor = init_visitor();
            visit(visitor, root);
        }
    }
    return 0;
}
