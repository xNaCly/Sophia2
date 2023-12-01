#include "token.h"
#include <stdio.h>

static char *TOKEN_TYPE_LOOKUP[] = {[TOKEN_LEFT_PAREN] = "TOKEN_LEFT_PAREN",
                                    [TOKEN_RIGHT_PAREN] = "TOKEN_RIGHT_PAREN",
                                    [TOKEN_LEFT_BRACE] = "TOKEN_LEFT_BRACE",
                                    [TOKEN_RIGHT_BRACE] = "TOKEN_RIGHT_BRACE",
                                    [TOKEN_COMMA] = "TOKEN_COMMA",
                                    [TOKEN_DOT] = "TOKEN_DOT",
                                    [TOKEN_MINUS] = "TOKEN_MINUS",
                                    [TOKEN_PLUS] = "TOKEN_PLUS",
                                    [TOKEN_SEMICOLON] = "TOKEN_SEMICOLON",
                                    [TOKEN_SLASH] = "TOKEN_SLASH",
                                    [TOKEN_STAR] = "TOKEN_STAR",
                                    [TOKEN_BANG] = "TOKEN_BANG",
                                    [TOKEN_BANG_EQUAL] = "TOKEN_BANG_EQUAL",
                                    [TOKEN_EQUAL] = "TOKEN_EQUAL",
                                    [TOKEN_EQUAL_EQUAL] = "TOKEN_EQUAL_EQUAL",
                                    [TOKEN_GREATER] = "TOKEN_GREATER",
                                    [TOKEN_GREATER_EQUAL] =
                                        "TOKEN_GREATER_EQUAL",
                                    [TOKEN_LESS] = "TOKEN_LESS",
                                    [TOKEN_LESS_EQUAL] = "TOKEN_LESS_EQUAL",
                                    [TOKEN_IDENTIFIER] = "TOKEN_IDENTIFIER",
                                    [TOKEN_STRING] = "TOKEN_STRING",
                                    [TOKEN_NUMBER] = "TOKEN_NUMBER",
                                    [TOKEN_AND] = "TOKEN_AND",
                                    [TOKEN_ELSE] = "TOKEN_ELSE",
                                    [TOKEN_FALSE] = "TOKEN_FALSE",
                                    [TOKEN_FOR] = "TOKEN_FOR",
                                    [TOKEN_FUNCTION] = "TOKEN_FUNCTION",
                                    [TOKEN_STRUCT] = "TOKEN_STRUCT",
                                    [TOKEN_IF] = "TOKEN_IF",
                                    [TOKEN_NIL] = "TOKEN_NIL",
                                    [TOKEN_OR] = "TOKEN_OR",
                                    [TOKEN_PRINT] = "TOKEN_PRINT",
                                    [TOKEN_RETURN] = "TOKEN_RETURN",
                                    [TOKEN_TRUE] = "TOKEN_TRUE",
                                    [TOKEN_VAR] = "TOKEN_VAR",
                                    [TOKEN_WHILE] = "TOKEN_WHILE",
                                    [TOKEN_ERROR] = "TOKEN_ERROR",
                                    [TOKEN_EOF] = "TOKEN_EOF"};

const char *tokentype_lookup(TokenType t) {
  if (t > ARRAY_SIZE(TOKEN_TYPE_LOOKUP)) {
    return "TOKEN_UNKNOWN";
  }
  return TOKEN_TYPE_LOOKUP[t];
}
