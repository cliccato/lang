#ifndef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct LEXER_STRUCT {
    char c;
    unsigned int i;
    char* conts;
} Lexer;

Lexer* init_lexer(char* conts);

void advance(Lexer* lexer);

void skip(Lexer* lexer);

Token* get_token(Lexer* lexer);

Token* get_string(Lexer* lexer);

Token* advance_token(Lexer* lexer, Token* token);

char* current_char(Lexer* lexer);
#endif