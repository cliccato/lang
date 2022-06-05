#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/lexer.h"
#include "lib/parser.h"
#define LIMITE 30

void help() {
    printf("da fare dopo\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    FILE *in;
    int i;

    if (argc == 2) {
        int len;
        char* extension;
        char* file = argv[1];

        len = strlen(argv[i]);
        extension = &argv[i][len-3];

        printf("%s", file);
        printf("%s", extension);

        if(strcmp(extension,".mc") == 0) {
            printf("Estensione trovata");
        };

        char input[LIMITE];
        
        while(1) {
            //lexer
            //parser
        }

    } else {
        help();
    }

    return 0;
}