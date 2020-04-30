//Bison-файл.

%token OR AND NOT EQUAL PLUS MINUS MULITPLY DIVIDE INTNUMBER FLOATNUMBER REMAINDER POW LEFTBR RIGHTBR
%right EQUAL
%left OR AND NOT
%left PLUS MINUS
%left MULTIPLY DIVIDE REMAINDER

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
