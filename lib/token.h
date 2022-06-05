#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT {
    enum {
        T_ID,
        T_EQUAL,
        T_STRING,
        T_SEMICOLON,
        T_LTONDA,
        T_RTONDA,
        T_RGRAFFA,
        T_LGRAFFA,
        T_VIRGOLA,
        T_EOF
    } type;

    char* value;
} Token;

Token* init_token(int type, char* value);

#endif