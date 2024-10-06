%{
#include <cstdlib>
#include <string>
#include "Parser.hpp"
%}

%option reentrant interactive noyywrap nodefault outfile="scanner.cpp" header="scanner.hpp"

%%
[ \t\n]+       {};
"("			   { return lisp::Parser::token::LPAREN; }
")"			   { return lisp::Parser::token::RPAREN; }
[[:digit:]]+   { yylval->emplace<int>(std::stoi(yytext)); return lisp::Parser::token::NUMBER; }
[[:alpha]]+    { yylval->emplace<std::string>(std::string(yytext));return lisp::Parser::token::SYMBOL; }
[+\-*/]        { yylval->emplace<std::string>(std::string(yytext));return lisp::Parser::token::SYMBOL;}
<<EOF>>        { return lisp::Parser::token::YYEOF; }
.	         printf("bad input character '%s' at line %d\n", yytext, yylineno);
%%

int main() {
    yyscan_t scanner;
    yylex_init(&scanner);
    lisp::Parser parser{ scanner };
    parser.parse();
    yylex_destroy(scanner);
	return 0;
}
