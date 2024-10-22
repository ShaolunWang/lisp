#include "lisp/ast.h"
#include "lisp/parser.h"
#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<Parser> parser = std::make_unique<Parser>();
  std::shared_ptr<Lisp::Program> prog = parser->parse_program();
  std::cout << prog->make_print() << '\n';
  return 0;
}
