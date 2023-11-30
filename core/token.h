#ifndef TOKEN_H_
#define TOKEN_H_

typedef enum TokenType {
  TOKEN_UNKNOWN,

  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_ASTERISK,
  TOKEN_SLASH,

  TOKEN_BRACE_LEFT,
  TOKEN_BRACE_RIGHT,

  TOKEN_EOF,
} TokenType;

typedef struct Token {
  TokenType type;
  char *raw;
} Token;

const char *tokentype_lookup(TokenType t);

#endif
