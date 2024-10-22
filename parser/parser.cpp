#include "lisp/parser.h"
#include "lisp/ast.h"
#include <cctype>
#include <iostream>
#include <memory>
#include <ostream>

int Parser::tok() {

  last_char = ' ';

  // Skip any whitespace.
  while (isspace(last_char)) {
    last_char = getchar();
  }

  if (isdigit(last_char)) { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += last_char;
      last_char = getchar();
    } while (isdigit(last_char) || last_char == '.');

    numVal = strtod(NumStr.c_str(), nullptr);
    return static_cast<int>(Token::tok_number);
  }

  if (last_char == '(') {
    return static_cast<int>(Token::tok_lBracket);
  }
  if (last_char == ')') {
    return static_cast<int>(Token::tok_rBracket);
  }

  // Check for end of file.  Don't eat the EOF.
  if (last_char == EOF) {
    return static_cast<int>(Token::tok_eof);
  }

  // Otherwise, just return the character as its ascii value.
  if (!isspace(last_char) && !isdigit(last_char)) {
    identifierStr = last_char;
    last_char = getchar();
    while (!isspace(last_char)) {
      identifierStr += last_char;
      last_char = getchar();
    }
  }
  //  return ThisChar;
  return last_char;
}

std::unique_ptr<Lisp::Number> Parser::parse_number() {
  auto result = std::make_unique<Lisp::Number>(numVal);
  return std::move(result);
}

std::unique_ptr<Lisp::ListExpr> Parser::parse_listExpr() {
  // list_expr ::= LB Expr RB
  // LB should be consumed
  //  getNextToken(); // LB
  std::vector<std::unique_ptr<Lisp::Expr>> list;
  //  auto result = std::make_unique<Lisp::Expr>(_a);
  if (static_cast<Token>(current_tok) != Token::tok_rBracket) {
    while (true) {
      if (auto item = parse_expr()) {
        list.emplace_back(std::move(item));
      } else {
		  // includes eof / rbracket cases
        break;
      }
    }
    getNextToken();
  }
  return std::make_unique<Lisp::ListExpr>(std::move(list));
}

std::unique_ptr<Lisp::Symbol> Parser::parse_symbol() {
  std::string symbol = identifierStr;
  return std::make_unique<Lisp::Symbol>(symbol);
}

std::unique_ptr<Lisp::Expr> Parser::parse_expr() {
  getNextToken();
  if (static_cast<Token>(current_tok) == Token::tok_lBracket) {
    return parse_listExpr();
  }
  if (static_cast<Token>(current_tok) == Token::tok_number) {
    return parse_number();
  }
  if (static_cast<Token>(current_tok) == Token::tok_eof) {
    return {};
  }
  if (static_cast<Token>(current_tok) == Token::tok_rBracket) {
    return {};
  }
  return parse_symbol();
}

std::unique_ptr<Lisp::Program> Parser::parse_program() {
  std::vector<std::unique_ptr<Lisp::Expr>> expr_list;
  while (static_cast<Token>(current_tok) != Token::tok_eof) {
    if (auto x = parse_expr()) {
      expr_list.push_back(std::move(x));
    } else {
      break;
    }
  }
  return std::make_unique<Lisp::Program>(std::move(expr_list));
}
