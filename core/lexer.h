#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"

typedef struct Lexer {
  int pos;
  char *input;
} Lexer;

Lexer *lexer_new(char *input);

Token *lexer_next(Lexer *l);

#endif
