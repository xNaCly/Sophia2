#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "lexer.h"
#include "lib/map.h"
#include "token.h"
#include "util.h"

static const TokenType KEYWORD_LIST[] = {
    TOKEN_AND,      TOKEN_ELSE, TOKEN_FALSE, TOKEN_FOR,   TOKEN_STRUCT,
    TOKEN_FUNCTION, TOKEN_IF,   TOKEN_NIL,   TOKEN_OR,    TOKEN_PRINT,
    TOKEN_RETURN,   TOKEN_TRUE, TOKEN_VAR,   TOKEN_WHILE,
};

static const char *const KEYWORDS[] = {
    [TOKEN_AND] = "and",       [TOKEN_ELSE] = "else",
    [TOKEN_FALSE] = "false",   [TOKEN_FOR] = "for",
    [TOKEN_STRUCT] = "struct", [TOKEN_FUNCTION] = "function",
    [TOKEN_IF] = "if",         [TOKEN_NIL] = "nil",
    [TOKEN_OR] = "or",         [TOKEN_PRINT] = "print",
    [TOKEN_RETURN] = "return", [TOKEN_TRUE] = "true",
    [TOKEN_VAR] = "var",       [TOKEN_WHILE] = "while",
};

Lexer lexer;

Map map;

void mapInit() {
  if (map.table_size != 0) {
    return;
  }
  map = *mapNew();
  for (size_t i = 0; i < ARRAY_SIZE(KEYWORD_LIST); i++) {
    TokenType *t = malloc(sizeof(TokenType));
    *t = KEYWORD_LIST[i];
    mapPut(&map, KEYWORDS[KEYWORD_LIST[i]], t);
  }
}

void mapClean() {
  for (size_t i = 0; i < ARRAY_SIZE(KEYWORD_LIST); i++) {
    TokenType t = KEYWORD_LIST[i];
    void *r = mapGet(&map, KEYWORDS[t]);
    free(r);
  }
  mapFree(&map);
}

void lexerInit(const char *input) {
  mapInit();
  lexer.start = input;
  lexer.current = input;
  lexer.line = 1;
}

static bool isInt(char c) { return (c >= '0' && c <= '9'); }
static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
static bool isAtEnd() { return *lexer.current == '\0'; }
static char peek() { return *lexer.current; }
static char advance() {
  lexer.current++;
  return lexer.current[-1];
}
static Token makeToken(TokenType t) {
  Token tok;
  tok.type = t;
  tok.start = lexer.start;
  tok.length = (int)(lexer.current - lexer.start);
  tok.line = lexer.line;
  return tok;
}
static Token errorToken(const char *message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = lexer.line;
  return token;
}
static void skipWhitespace() {
  for (;;) {
    switch (peek()) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      lexer.line++;
      advance();
      break;
    case '#':
      while (peek() != '\n' && !isAtEnd())
        advance();
    default:
      return;
    }
  }
}
static Token string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      lexer.line++;
    advance();
  }

  if (isAtEnd())
    return errorToken("Unterminated String");

  advance();
  return makeToken(TOKEN_STRING);
}

static char peekNext() {
  if (isAtEnd())
    return '\0';
  return lexer.current[1];
}

static Token number() {
  while (isInt(peek()))
    advance();

  if (peek() == '.' && isInt(peekNext())) {
    advance();

    while (isInt(peek()))
      advance();
  }

  return makeToken(TOKEN_NUMBER);
}

static TokenType identifierType() {
  const char *ident = lexer.start;
  TokenType *r = (TokenType *)mapGet(&map, ident);
  if (r == NULL) {
    return TOKEN_IDENTIFIER;
  }
  return *r;
}

static Token identifier() {
  while (isInt(peek()) || isAlpha(peek()))
    advance();
  return makeToken(identifierType());
}

static bool match(char expected) {
  if (isAtEnd())
    return false;
  if (*lexer.current != expected)
    return false;
  lexer.current++;
  return true;
}

Token lexerNext() {
  skipWhitespace();
  lexer.start = lexer.current;

  if (isAtEnd())
    return makeToken(TOKEN_EOF);

  char c = advance();
  if (isAlpha(c))
    return identifier();
  if (isInt(c))
    return number();

  switch (c) {
  case '(':
    return makeToken(TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(TOKEN_SEMICOLON);
  case ',':
    return makeToken(TOKEN_COMMA);
  case '.':
    return makeToken(TOKEN_DOT);
  case '-':
    return makeToken(TOKEN_MINUS);
  case '+':
    return makeToken(TOKEN_PLUS);
  case '/':
    return makeToken(TOKEN_SLASH);
  case '*':
    return makeToken(TOKEN_STAR);
  case '!':
    return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  case '"':
    return string();
  }

  return errorToken("Unexpected character.");
}
