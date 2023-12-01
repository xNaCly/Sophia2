#include <stdio.h>
#include <stdlib.h>

#include "sophia/common.h"
#include "sophia/lexer.h"
#include "sophia/lib/map.h"
#include "sophia/token.h"
#include "sophia/util.h"

#define PROMPT "> "

static void start(const char *input) {
  lexerInit(input);
  int line = -1;
  for (;;) {
    Token token = lexerNext();
    if (token.line != line) {
      printf("%4d ", token.line);
      line = token.line;
    } else {
      printf("   | ");
    }
    printf("[%15s] '%.*s'\n", tokentype_lookup(token.type), token.length,
           token.start);

    if (token.type == TOKEN_EOF)
      break;
  }
}

static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(EXIT_FAILURE);
  }
  fseek(file, 0L, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char *buffer = NULL;
  if (buffer = malloc(size + 1), buffer == NULL) {
    error("Failed to allocate buffer for file content");
  }
  size_t readBytes = fread(buffer, sizeof(char), size, file);
  if (readBytes < size) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(EXIT_FAILURE);
  }
  fclose(file);
  return buffer;
}

static void repl() {
  char l[1024];
  for (;;) {
    printf(PROMPT);

    if (!fgets(l, sizeof(l), stdin)) {
      printf("\n");
      break;
    }
    start(l);
  }
}

int main(int argc, const char *argv[]) {
  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    char *buf = readFile(argv[1]);
    start(buf);
  } else {
    error("Usage: sophia2 [path]");
  }
  atexit(mapClean);
  return EXIT_SUCCESS;
}
