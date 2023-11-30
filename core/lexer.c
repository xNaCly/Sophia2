#include "lexer.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

Lexer *lexer_new(char *input) {
  Lexer *l = NULL;
  if (l = malloc(sizeof(Lexer)), l == NULL) {
    error("Failed to allocate lexer");
    exit(1);
  }
  l->pos = 0;
  l->input = input;
  return l;
}

static char peek(Lexer *l) { return l->input[l->pos]; }

static void advance(Lexer *l) {
  if (peek(l) == 0) {
    return;
  }
  l->pos++;
}

static Token *number(Lexer *l) {
  char c = peek(l);
  while ((c >= '0' && c <= '9') || c == '.') {
    TODO();
  }
  advance(l);
  return NULL;
}

Token *lexer_next(Lexer *l) {
  char c = peek(l);
  TokenType t = TOKEN_UNKNOWN;
  switch (c) {
  case 0:
    t = TOKEN_EOF;
    break;
  case '+':
    t = TOKEN_PLUS;
    break;
  case '-':
    t = TOKEN_MINUS;
    break;
  case '/':
    t = TOKEN_SLASH;
    break;
  case '*':
    t = TOKEN_ASTERISK;
    break;
  case '(':
    t = TOKEN_BRACE_LEFT;
    break;
  case ')':
    t = TOKEN_BRACE_RIGHT;
    break;
  default:
    if (c >= '0' && c <= '9') {
      return number(l);
    } else {
      fprintf(stderr, "Unknown character '%c'\n", c);
    }
  }
  advance(l);
  Token *tok = NULL;
  if (tok = malloc(sizeof(Token)), tok == NULL) {
    error("Failed to allocate Token");
  }
  tok->type = t;
  return tok;
}