#include "lisp/ast.h"

std::string Lisp::Program::make_print() const {
  std::string s;
  for (int i = 0; i < sexpr.size(); i++) {
    s += sexpr[i]->make_print();
  }
  return s;
};

std::string Lisp::ListExpr::make_print() const {
  std::string s = "ListExpr: {\n";
  for (int i = 0; i < listExpr.size(); i++) {
    s += "\t" + listExpr[i]->make_print();
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

