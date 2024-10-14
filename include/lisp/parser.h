#ifndef _PARSER_H_
#include "ast.h"

class Parser {
public:
  enum class Token {
    tok_eof = -1,
    tok_lBracket = -2,
    tok_rBracket = -3,
    tok_symbol = -4,
    tok_number = -5,
  };

public:
  std::unique_ptr<Lisp::Program> driver();
  int parse_tok();

private:
  int lastChar;
  std::string identifierStr;
  int numVal;
};

#endif
