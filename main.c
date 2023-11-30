#include <stdio.h>
#include <stdlib.h>

#include "core/lexer.h"
#include "core/token.h"
#include "core/util.h"

int main(void) {
  Lexer *l = lexer_new("+-*/()12");
  Token *t = lexer_next(l);
  while (t->type != TOKEN_EOF) {
    printf("%s\n", tokentype_lookup(t->type));
    t = lexer_next(l);
  }
  return EXIT_SUCCESS;
}
