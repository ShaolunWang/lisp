#pragma once
#include "lisp/ast.h"
#include "lisp/parser.h"
#include <iostream>
#include <memory>

int main() {

  std::shared_ptr<Lisp::Program> program =
      std::make_shared<Lisp::Program>(Lisp::Program());

  std::unique_ptr<Lisp::Symbol> s =
      std::make_unique<Lisp::Symbol>(Lisp::Symbol("a"));

  std::unique_ptr<Lisp::Symbol> p =
      std::make_unique<Lisp::Symbol>(Lisp::Symbol("+"));

  std::vector<std::unique_ptr<Lisp::Expr>> v;

  v.push_back(std::move(p));
  v.push_back(std::move(s));
  v.push_back(std::move(std::make_unique<Lisp::Number>(Lisp::Number(1))));

  std::unique_ptr<Lisp::ListExpr> ss =
      std::make_unique<Lisp::ListExpr>(std::move(v));
  program->sexpr.push_back(std::move(ss));
  std::cout << program->make_print() << std::endl;

  std::unique_ptr<Parser> parser = std::make_unique<Parser>();
  while (true) {
    int a = parser->parse_tok();
    if (a == static_cast<int>(Parser::Token::tok_eof)) {
      break;
    } else
      std::cout << std::to_string(a) << std::endl;
  }
  return 0;
}
