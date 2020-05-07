%token INTNUMBER
%token FLOATNUMBER
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

/*
%right EQUAL

%left OR AND NOT
%left PLUS MINUS
%left MULTIPLY DIVIDE REMAINDER
*/

%{
      #include <iostream>
      using namespace std;
%}

%%

expr1: mul_expr
        | expr1 PLUS expr2  { $$ = $1 + $3; }
        | expr1 MINUS expr2 { $$ = $1 - $3; }
        ;
expr2: primary
        | expr2 MULTIPLY primary { $$ = $1 * $3; }
        | expr2 DIVIDE primary { $$ = $1 / $3; }
        | expr2 REMAINDER primary { $$ = $1 % $3; }
        ;
primary: FLOATNUMBER { $$ = $1; }
        | INTNUMBER { $$ = $1; }
        ;

%%

yylex();
