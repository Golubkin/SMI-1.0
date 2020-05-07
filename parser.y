%{
      #include <stdio.h>
      #include <stdlib.h>
      extern int yylex();
      extern int yyparse();
      extern FILE* yyin;
      void yyerror(const char *s);
%}

%union { int one; float two; }

%token<one> INTNUMBER
%token<two> FLOATNUMBER

%token NEWLINE
%token EXIT
%token EQUAL
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token REMAINDER
%token LB
%token RB
%token COMMA
%token COMMENT
%token AND
%token OR
%token NOT
%token TFLOOR
%token TCEIL
%token TROUND
%token TABC
%token TPOW
%token TSQRT
%token TFACT
%token TSIN
%token TCOS
%token TTG
%token TEXP
%token TLN
%token TLOG
%token IF
%token ELSE
%token WHILE
%token FOR

%right EQUAL

%left OR AND NOT
%left PLUS MINUS
%left MULTIPLY DIVIDE REMAINDER

%type<one> expr1
%type<two> expr2

%start calculation

%%

calculation:
	   | calculation line
;

line: NEWLINE
    | expr2 NEWLINE { printf("\tResult: %f\n", $1);}
    | expr1 NEWLINE { printf("\tResult: %i\n", $1); }
    | EXIT NEWLINE { printf("bye!\n"); exit(0); }
;
expr2: FLOATNUMBER               { $$ = $1; }
     | expr2 PLUS expr2	         { $$ = $1 + $3; }
     | expr2 MINUS expr2	   { $$ = $1 - $3; }
     | expr2 MULTIPLY expr2 	   { $$ = $1 * $3; }
     | expr2 DIVIDE expr2	   { $$ = $1 / $3; }
     | LB expr2 RB  	         { $$ = $2; }
     | expr1 PLUS expr2	 	   { $$ = $1 + $3; }
     | expr1 MINUS expr2	   { $$ = $1 - $3; }
     | expr1 MULTIPLY expr2 	   { $$ = $1 * $3; }
     | expr1 DIVIDE expr2	   { $$ = $1 / $3; }
     | expr2 PLUS expr1	 	   { $$ = $1 + $3; }
     | expr2 MINUS expr1	   { $$ = $1 - $3; }
     | expr2 MULTIPLY expr1 	   { $$ = $1 * $3; }
     | expr2 DIVIDE expr1	   { $$ = $1 / $3; }
     | expr1 DIVIDE expr1 	   { $$ = $1 / (float)$3; }
;

expr1: INTNUMBER			   { $$ = $1; }
     | expr1 PLUS expr1		   { $$ = $1 + $3; }
     | expr1 MINUS expr1	   { $$ = $1 - $3; }
     | expr1 MULTIPLY expr1	   { $$ = $1 * $3; }
     | LB expr1 RB		   { $$ = $2; }
;

%%

int main() {
	yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
