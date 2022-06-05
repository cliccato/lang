#include <stdlib.h>
#include <string.h>
#include "lib/lexer.h"

Lexer* init_lexer(char* conts) {
    Lexer* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->conts = conts;
    lexer->i = 0;
    lexer->c = conts[lexer->i];

    return lexer;
}

void advance(Lexer* lexer) {
    int n_conts = strlen(lexer->conts);

    if (lexer->c != '\0' && lexer->i < n_conts) {
        lexer->i += 1;
        lexer->c = lexer->conts[lexer->i];
    }
}

void skip(Lexer* lexer) {
    while (lexer->c == ' ' || lexer->c == 10) {  //10 e' \n in ascii
        advance(lexer);
    }
}

Token* advance_token(Lexer* lexer, Token* token) {
    advance(lexer);
    return token;
}

Token* get_token(Lexer* lexer) {
    int n_conts = strlen(lexer->conts);
    Token* token;

    while (lexer->c == ' ' && lexer->i < n_conts) {
        if (lexer->c == ' ' || lexer->c == 10) {    //se c'e' uno spazio
            skip(lexer);
        }

        switch(lexer->c) {
            case '=':
                token = init_token(T_EQUAL, current_char(lexer));
                return advance_token(lexer, token);
                break;
            case ',':
                token = init_token(T_VIRGOLA, current_char(lexer));
                return advance_token(lexer, token);
                break;
            case ';':
                token = init_token(T_SEMICOLON, current_char(lexer));
                return advance_token(lexer, token);
                break;
            case '(':
                token = init_token(T_LTONDA, current_char(lexer));
                return advance_token(lexer, token);
                break;
            case ')':
                token = init_token(T_RTONDA, current_char(lexer));
                return advance_token(lexer, token);
                break;
            case '{':
                token = init_token(T_LGRAFFA, current_char(lexer));
                return advance_token(lexer, token);
                break;
            case '}':
                token = init_token(T_RGRAFFA, current_char(lexer));
                return advance_token(lexer, token);
                break;
        }
    }
}

char* current_char(Lexer* lexer) {
    char* string = calloc(2, sizeof(char));

    string[0] = lexer->c;
    string[1] = '\0';

    return string;
}

/*
Token* get_string(Lexer* lexer) {

}
*/