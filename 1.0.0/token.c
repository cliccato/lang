#include "lib/token.h"
#include <stdlib.h>


Token* init_token(int type, char* value)
{
    Token* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = value;

    return token;
}
