#ifndef lexer_h_
#define lexer_h_

#include "token.h"

typedef struct {
  const char *start;
  const char *current;
  int line;
} Lexer;

void lexerInit(const char *input);
void mapClean();

Token lexerNext();

#endif
