#ifndef _AST_NODE_H
#define _AST_NODE_H
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace Lisp {
class Expr {
public:
  Expr() = default;
  virtual ~Expr() = default;
  virtual std::string make_print() const = 0;
};

class Program {
public:
  std::vector<std::unique_ptr<Expr>> sexpr;
  std::string make_print() const;
};

class ListExpr : public Expr {
public:
  explicit ListExpr(std::vector<std::unique_ptr<Expr>> listExpr)
      : listExpr(std::move(listExpr)) {}
  std::vector<std::unique_ptr<Expr>> listExpr{};
  std::string make_print() const override;
};
class Literal : public Expr {
public:
  Literal() = default;
  virtual ~Literal() = default;
};

class Symbol : public Literal {
public:
  Symbol(std::string name) : name{name} {}
  std::string name;
  std::string make_print() const override;
};

class Number : public Literal {
public:
  Number(int value) : value{value} {}
  int value;
  std::string make_print() const override;
};

}; // namespace Lisp

#endif
