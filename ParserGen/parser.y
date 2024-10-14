%{
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include "scanner.hpp"
%}

%require "3.7.4"
%language "C++"
%defines "Parser.hpp"
%output "Parser.cpp"

%define api.parser.class {Parser}
%define api.namespace {lisp}
%define api.value.type variant
%param {yyscan_t scanner}
%code provides
{
    #define YY_DECL \
        int yylex(lisp::Parser::semantic_type *yylval, yyscan_t yyscanner)
    YY_DECL;
}
 

// %union {
// char *str;
// int num;
// }

%token LPAREN RPAREN /* need them to check prec */
%token <std::string> NEWLINE
%token <std::string> SYMBOL /* symbols are strings */
%token <int> NUMBER
%nterm <std::string> EXPR
%nterm <std::string> LIST
%nterm <std::string> EXPR_LIST
%%
PROG: /* empty */
	| PROG EXPR

/* (+ (1 2)) */
/* LPAREN EXPR_LIST RPAREN */
/* where EXPR_LIST =>  (1, 2) */
LIST: LPAREN EXPR_LIST RPAREN {std::cout<< "LPAREN ";} /* first parsed */

EXPR_LIST:  {}
		 | EXPR EXPR_LIST  {std::cout << $1 << " ";} 

EXPR: SYMBOL {std::cout<<"{SYMBOL: "<< $1 << "} ";}
	| NUMBER {std::cout<< "{NUMBER: " << $1 << "} ";}
	| LIST   {std::cout<< "RPAREN ";} /* last parsed */
	| NEWLINE  {std::cout<< "\n";}

%%

void lisp::Parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}
