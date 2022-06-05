#ifndef LEXER_H
#define LEXER_H
#include "token.h"


typedef struct LEXER_STRUCT
{
    char c;
    unsigned int i;
    char* contents;
} Lexer;

Lexer* init_lexer(char* contents);

void advance(Lexer* lexer);

void skip_whitespace(Lexer* lexer);

Token* get_next_token(Lexer* lexer);

Token* collect_str(Lexer* lexer);

Token* collect_id(Lexer* lexer);

Token* advance_with_token(Lexer* lexer, Token* token);

char* get_current_char_as_str(Lexer* lexer);
#endif
