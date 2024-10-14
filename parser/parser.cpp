#include "lisp/parser.h"
#include <memory>

std::unique_ptr<Lisp::Program> Parser::driver() {
  std::unique_ptr<Lisp::Program> p = std::make_unique<Lisp::Program>();
  return p;
}

int Parser::parse_tok() {

  lastChar = ' ';

  // Skip any whitespace.
  while (isspace(lastChar))
    lastChar = getchar();

  if (isalpha(lastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    identifierStr = lastChar;
    while (isalnum((lastChar = getchar())))
      identifierStr += lastChar;

    return static_cast<int>(Token::tok_symbol);
  }

  if (isdigit(lastChar) || lastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += lastChar;
      lastChar = getchar();
    } while (isdigit(lastChar) || lastChar == '.');

    numVal = strtod(NumStr.c_str(), nullptr);
    return static_cast<int>(Token::tok_number);
  }

  if (lastChar == '(')
    return static_cast<int>(Token::tok_lBracket);
  if (lastChar == ')')
    return static_cast<int>(Token::tok_rBracket);

  // Check for end of file.  Don't eat the EOF.
  if (lastChar == EOF)
    return static_cast<int>(Token::tok_eof);

  // Otherwise, just return the character as its ascii value.
  int ThisChar = lastChar;
  lastChar = getchar();
  //  return ThisChar;
  return static_cast<int>(Token::tok_symbol);
}
