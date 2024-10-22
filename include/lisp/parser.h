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
  std::unique_ptr<Lisp::Number> parse_number();
  std::unique_ptr<Lisp::Symbol> parse_symbol();
  std::unique_ptr<Lisp::ListExpr> parse_listExpr();
  std::unique_ptr<Lisp::Expr> parse_expr();
  std::unique_ptr<Lisp::Program> parse_program();
  int getNextToken(){
	return current_tok = tok();
  };

  int tok();

private:
  int last_char;
  int current_tok;
  std::string identifierStr;
  int numVal;
};

#endif
