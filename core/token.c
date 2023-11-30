#include "token.h"

static const char *const TOKEN_TYPE_LOOKUP[] = {
    [TOKEN_UNKNOWN] = "TOKEN_UNKNOWN",
    [TOKEN_NUMBER] = "TOKEN_NUMBER",
    [TOKEN_PLUS] = "TOKEN_PLUS",
    [TOKEN_MINUS] = "TOKEN_MINUS",
    [TOKEN_ASTERISK] = "TOKEN_ASTERISK",
    [TOKEN_SLASH] = "TOKEN_SLASH",
    [TOKEN_BRACE_LEFT] = "TOKEN_BRACE_LEFT",
    [TOKEN_BRACE_RIGHT] = "TOKEN_BRACE_RIGHT",
    [TOKEN_EOF] = "TOKEN_EOF",
};

const char *tokentype_lookup(TokenType t) { return TOKEN_TYPE_LOOKUP[t]; }
