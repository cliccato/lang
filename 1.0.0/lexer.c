#include "lib/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


Lexer* init_lexer(char* contents)
{
    Lexer* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void advance(Lexer* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

void skip_whitespace(Lexer* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10)
    {
        advance(lexer);
    }
}

Token* get_next_token(Lexer* lexer)
{
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
    {
        if (lexer->c == ' ' || lexer->c == 10)
            skip_whitespace(lexer);

        if (isalnum(lexer->c))
            return collect_id(lexer);

        if (lexer->c == '"')
            return collect_str(lexer);

        switch (lexer->c)
        {
            case '=': return advance_with_token(lexer, init_token(TOKEN_EQUAL, get_current_char_as_str(lexer))); break;
            case ';': return advance_with_token(lexer, init_token(TOKEN_SEMICOLON, get_current_char_as_str(lexer))); break;
            case '(': return advance_with_token(lexer, init_token(TOKEN_LTONDA, get_current_char_as_str(lexer))); break;
            case ')': return advance_with_token(lexer, init_token(TOKEN_RTONDA, get_current_char_as_str(lexer))); break;
            case '{': return advance_with_token(lexer, init_token(TOKEN_LGRAFFA, get_current_char_as_str(lexer))); break;
            case '}': return advance_with_token(lexer, init_token(TOKEN_RGRAFFA, get_current_char_as_str(lexer))); break;
            case ',': return advance_with_token(lexer, init_token(TOKEN_VIGOLA, get_current_char_as_str(lexer))); break;
        }
    }

    return init_token(TOKEN_EOF, "\0");
}

Token* collect_str(Lexer* lexer)
{
    advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"')
    {
        char* s = get_current_char_as_str(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        advance(lexer);
    }

    advance(lexer);

    return init_token(TOKEN_STR, value);
}

Token* collect_id(Lexer* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c))
    {
        char* s = get_current_char_as_str(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

Token* advance_with_token(Lexer* lexer, Token* token)
{
    advance(lexer);

    return token;
}

char* get_current_char_as_str(Lexer* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}
