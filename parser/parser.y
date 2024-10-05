%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* declare because we need to use them, reminder that this is c not cpp */
void yyerror(const char *s);
void yywrap(const char *s);
int yylex();
%}

%union {
char *str;
int num;
}
%token LPAREN RPAREN /* need them to check prec */
%token <str> NEWLINE
%token <str> SYMBOL /* symbols are strings */
%token <num> NUMBER
%type <str> EXPR
%type <str> LIST
%type <str> EXPR_LIST
%%
PROG: /* empty */
	| PROG EXPR

/* (+ (1 2)) */
/* LPAREN EXPR_LIST RPAREN */
/* where EXPR_LIST =>  (1, 2) */
LIST: LPAREN EXPR_LIST RPAREN /*{printf("RPAREN ");}*/

EXPR_LIST: /*{$$ = NULL;} */
		 | EXPR EXPR_LIST /* {printf("{%s}", $1);} */

EXPR: SYMBOL 
	| NUMBER /*{printf("{NUMBER %d} ", $1);} */
	| LIST  /* {printf("LPAREN ");} */
	| NEWLINE /* {printf("\n");} */
%%

void yyerror(const char *s){
	fprintf(stderr, "ERROR: %s\n", s);
}
int main(){
	yyparse();
	return 0;
}
