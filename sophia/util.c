#include "util.h"
#include <stdio.h>
#include <stdlib.h>

// prints txt, exits
void error(const char *txt) {
  fprintf(stderr, "err: %s\n", txt);
  exit(EXIT_FAILURE);
}
