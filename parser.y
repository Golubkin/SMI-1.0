%{
      #include <stdio.h>
      #include <stdlib.h>
      #include "MathFunctions.cpp"
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
%token LC
%token RC
%token AND
%token OR
%token NOT
%token TFLOOR
%token TCEIL
%token TROUND
%token TABS
%token TPOW
%token TSQRT
%token TFACT
%token TSIN
%token TCOS
%token TTG
%token TCTG
%token TEXP
%token TLN
%token TLOG
%token IF
%token ELSE
%token WHILE
%token FOR

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
expr2: FLOATNUMBER              		 { $$ = $1; }
     | expr2 PLUS expr2	         		 { $$ = $1 + $3; }
     | expr2 MINUS expr2	  		 { $$ = $1 - $3; }
     | expr2 MULTIPLY expr2 	  		 { $$ = $1 * $3; }
     | expr2 DIVIDE expr2	  		 { $$ = $1 / $3; }
     | LB expr2 RB  	        		 { $$ = $2; }
     | TFLOOR LC expr2 RC       		 { $$ = SMIfloor($3); }
     | TCEIL LC expr2 RC        		 { $$ = SMIceil($3); }
     | TROUND LC expr2 RC         		 { $$ = SMIround($3); }
     | TABS LC expr2 RC            		 { $$ = SMIabs($3); }
     | TLN LC expr2 RC         			 { $$ = SMIln($3); }
     | TEXP LC expr2 RC       		         { $$ = SMIexp($3); }
     | TSQRT LC expr2 RC        		 { $$ = SMIsqrt($3); }
     | TSIN LC expr2 RC       			 { $$ = SMIsin($3); }
     | TCOS LC expr2 RC       			 { $$ = SMIcos($3); }
     | TTG LC expr2 RC        			 { $$ = SMItg($3); }
     | TCTG LC expr2 RC      			 { $$ = SMIctg($3); }
     | TPOW LC expr2 COMMA expr2 RC  		 { $$ = SMIpow($3, $5); }
     | TLOG LC expr2 COMMA expr2 RC  		 { $$ = SMIlog($3, $5); }
     | expr1 PLUS expr2	 	   		 { $$ = $1 + $3; }
     | expr1 MINUS expr2	      		 { $$ = $1 - $3; }
     | expr1 MULTIPLY expr2 	   		 { $$ = $1 * $3; }
     | expr1 DIVIDE expr2	   		 { $$ = $1 / $3; }
     | TPOW LC expr1 COMMA expr2 RC  		 { $$ = SMIpow($3, $5); }
     | TLOG LC expr1 COMMA expr2 RC  		 { $$ = SMIlog($3, $5); }
     | expr2 PLUS expr1	 	   		 { $$ = $1 + $3; }
     | expr2 MINUS expr1	   		 { $$ = $1 - $3; }
     | expr2 MULTIPLY expr1 	   		 { $$ = $1 * $3; }
     | expr2 DIVIDE expr1	  		 { $$ = $1 / $3; }
     | TPOW LC expr2 COMMA expr1 RC  		 { $$ = SMIpow($3, $5); }
     | TLOG LC expr2 COMMA expr1 RC  		 { $$ = SMIlog($3, $5); }
     | expr1 DIVIDE expr1 	   		 { $$ = $1 / (float)$3; }
     | expr1 REMAINDER expr1                     { $$ = $1 % $3; }
     | TPOW LC expr1 COMMA expr1 RC  		 { $$ = SMIpow($3, $5); }
     | TLOG LC expr1 COMMA expr1 RC  		 { $$ = SMIlog($3, $5); }
;

expr1: INTNUMBER			     	 { $$ = $1; }
     | expr1 PLUS expr1		   		 { $$ = $1 + $3; }
     | expr1 MINUS expr1	   		 { $$ = $1 - $3; }
     | expr1 MULTIPLY expr1	   		 { $$ = $1 * $3; }
     | LB expr1 RB		   		 { $$ = $2; }
     | TFLOOR LC expr1 RC          		 { $$ = SMIfloor($3); }
     | TCEIL LC expr1 RC        		 { $$ = SMIceil($3); }
     | TROUND LC expr1 RC         		 { $$ = SMIround($3); }
     | TABS LC expr1 RC            		 { $$ = SMIabs($3); }
     | TFACT LC expr1 RC          		 { $$ = SMIfact($3); }
     | TLN LC expr1 RC          		 { $$ = SMIln($3); }
     | TEXP LC expr1 RC         		 { $$ = SMIexp($3); }
     | TSQRT LC expr1 RC         		 { $$ = SMIsqrt($3); }
     | TSIN LC expr1 RC       			 { $$ = SMIsin($3); }
     | TCOS LC expr1 RC       			 { $$ = SMIcos($3); }
     | TTG LC expr1 RC        			 { $$ = SMItg($3); }
     | TCTG LC expr1 RC      			 { $$ = SMIctg($3); }
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
}
