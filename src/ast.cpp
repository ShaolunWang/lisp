#include "lisp/ast.h"

std::string Lisp::Program::make_print() const {
  std::string s;
  for (const auto & i : sexpr) {
    s += i->make_print();
  }
  return s;
};

std::string Lisp::ListExpr::make_print() const {
  std::string s = "ListExpr: {\n";
  for (const auto & i : listExpr) {
    s += "\t" + i->make_print();
  }
  s += " }\n";
  return s;
}

std::string Lisp::Number::make_print() const {
  return std::string(" {Integer: " + std::to_string(value)+  " }\n");
}

std::string Lisp::Symbol::make_print() const {

  return std::string(" {Symbol: " + name + " }\n");
}

