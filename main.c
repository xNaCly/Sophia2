#include <stdio.h>
#include <stdlib.h>

#include "core/lexer.h"
#include "core/token.h"
#include "core/util.h"

// TODO:
/* - parser */
/* - bytecode vm */
/* - copy growing array and hashmap from seascript */
/* - use growing array to implement a string builder */
/* - language features: */
/*     - arithmetic */
/*     - printing to stdout */
/*     - variables */

int main(void) {
  Lexer *l = lexer_new("+-*/()12");
  Token *t = lexer_next(l);
  while (t->type != TOKEN_EOF) {
    printf("%s\n", tokentype_lookup(t->type));
    t = lexer_next(l);
  }
  TODO();
  return EXIT_SUCCESS;
}
