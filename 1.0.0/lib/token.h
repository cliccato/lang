#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_ID,
        TOKEN_EQUAL,
        TOKEN_STR,
        TOKEN_SEMICOLON,
        TOKEN_LTONDA,
        TOKEN_RTONDA,
        TOKEN_RGRAFFA,
        TOKEN_LGRAFFA,
        TOKEN_VIGOLA,
        TOKEN_EOF
    } type;

    char* value;
} Token;

Token* init_token(int type, char* value);
#endif
