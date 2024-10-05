%option noyywrap
%{
#include <cstdlib>
#include "parser.hpp"
using namespace lisp;
%}

%option reentrant interactive noyywrap noyylineno nodefault outfile="scanner.cpp" header="scanner.hpp"

integer         ([[:digit:]]+)
symbol          ([[:alpha:]]+) 

%%
{symbol} 	 yylval->emplace<char>(yytext[0]); return Parser::token::INTVAR; 
{integer}    yylval->emplace<long long>(strtoll(yytext, nullptr, 10)); return Parser::token::INT; 
"(" { return Parser::token::LPAREN; }
")" { return Parser::token::RPAREN; }
<<EOF>>     {return Parser::token::YYEOF; }
.           /* no action on unmatched input */
%%

int main() {
    yyscan_t scanner;
    yylex_init(&scanner);
    calc::Parser parser{ scanner };
 //   std::cout.precision(10);
    parser.parse();
    yylex_destroy(scanner);
}
