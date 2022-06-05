#include <stdlib.h>
#include "lib/token.h"

Token* init_token(int type, char* val) {
    Token* t;
    t = calloc(2, sizeof(struct TOKEN_STRUCT));
    t->type = type;
    t->value = val;
    return t;
}