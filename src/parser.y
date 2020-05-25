%{
      #include <stdio.h>
      #include <stdlib.h>
      #include "src/MathFunctions/MathFunctions.cpp"
      int yylex();
      double sym[26];
      void yyerror(const char *s);
%}

%union { int one; float two; int var; char* say; }

%token<one> INTNUMBER
%token<two> FLOATNUMBER
%token<var> VARIABLE
%token<say> COM

%token NEWLINE
%token EXIT
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token REMAINDER
%token LB
%token RB
%token LSQ
%token RSQ
%token LESS
%token MORE
%token LESSOR
%token MOREOR
%token EQUAL
%token NEQUAL
%token SETVALUE
%token COMMA
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
%token SAY
%token CYCLE

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
    | expr1 SETVALUE expr2                      			 { sym[$1] = $3; }
    | expr1 SETVALUE expr1                      			 { sym[$1] = $3; }
    | expr2 NEWLINE                             			 { printf("\tResult: %f\n", $1); }
    | expr1 NEWLINE                             			 { printf("\tResult: %i\n", $1); }
    | EXIT NEWLINE                              			 { printf("bye!\n"); exit(0); }
;
expr2: FLOATNUMBER              					 { $$ = $1; }
     | MINUS FLOATNUMBER                        			 { $$ = -$2; }
     | VARIABLE                                 			 { $$ = sym[$1]; }
     | MINUS VARIABLE                           			 { $$ = -sym[$2]; }
     | expr2 PLUS expr2	         					 { $$ = $1 + $3; }
     | expr2 MINUS expr2	  					 { $$ = $1 - $3; }
     | expr2 MULTIPLY expr2 	  					 { $$ = $1 * $3; }
     | expr2 DIVIDE expr2	  					 { $$ = $1 / $3; }
     | expr2 REMAINDER expr2                    			 { $$ = (int)$1 % (int)$3; }              
     | LB expr2 RB  	        					 { $$ = $2; }
     | TFLOOR LSQ expr2 RSQ      					 { $$ = SMIfloor($3); }
     | TCEIL LSQ expr2 RSQ        					 { $$ = SMIceil($3); }
     | TROUND LSQ expr2 RSQ         					 { $$ = SMIround($3); }
     | TABS LSQ expr2 RSQ            					 { $$ = SMIabs($3); }
     | TLN LSQ expr2 RSQ         	        			 { $$ = SMIln($3); }
     | TEXP LSQ expr2 RSQ       	        			 { $$ = SMIexp($3); }
     | TSQRT LSQ expr2 RSQ        					 { $$ = SMIsqrt($3); }
     | TSIN LSQ expr2 RSQ       					 { $$ = SMIsin($3); }
     | TCOS LSQ expr2 RSQ       					 { $$ = SMIcos($3); }
     | TTG LSQ expr2 RSQ        					 { $$ = SMItg($3); }
     | TCTG LSQ expr2 RSQ      						 { $$ = SMIctg($3); }
     | TFACT LSQ expr2 RSQ          					 { $$ = SMIfact($3); }
     | TPOW LSQ expr2 COMMA expr2 RSQ  					 { $$ = SMIpow($3, $5); }
     | TLOG LSQ expr2 COMMA expr2 RSQ  					 { $$ = SMIlog($3, $5); }
     | SAY LSQ expr2 LESS expr2 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3<$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 MORE expr2 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3>$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 LESSOR expr2 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3<=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 MOREOR expr2 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3>=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 EQUAL expr2 RSQ LSQ COM RSQ LSQ COM RSQ      	 { if($3==$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 NEQUAL expr2 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3!=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 LESS expr2 RSQ             			 { if($3<$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 MORE expr2 RSQ             			 { if($3>$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 LESSOR expr2 RSQ           			 { if($3<=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 MOREOR expr2 RSQ           			 { if($3>=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 EQUAL expr2 RSQ            			 { if($3==$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 NEQUAL expr2 RSQ          			         { if($3!=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | expr1 PLUS expr2	 	   					 { $$ = $1 + $3; }
     | expr1 MINUS expr2	      					 { $$ = $1 - $3; }
     | expr1 MULTIPLY expr2 	   					 { $$ = $1 * $3; }
     | expr1 DIVIDE expr2	   					 { $$ = $1 / $3; }
     | TPOW LSQ expr1 COMMA expr2 RSQ  					 { $$ = SMIpow($3, $5); }
     | TLOG LSQ expr1 COMMA expr2 RSQ  					 { $$ = SMIlog($3, $5); }
     | SAY LSQ expr1 LESS expr2 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3<$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 MORE expr2 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3>$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 LESSOR expr2 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3<=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 MOREOR expr2 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3>=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 EQUAL expr2 RSQ LSQ COM RSQ LSQ COM RSQ      	 { if($3==$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 NEQUAL expr2 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3!=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 LESS expr2 RSQ              			 { if($3<$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 MORE expr2 RSQ             			 { if($3>$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 LESSOR expr2 RSQ           			 { if($3<=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 MOREOR expr2 RSQ           			 { if($3>=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 EQUAL expr2 RSQ            			 { if($3==$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 NEQUAL expr2 RSQ          			         { if($3!=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | CYCLE LSQ expr1 RSQ LSQ expr2 RSQ        			 { $$ = $3; while($3 > 0){printf("%f\n", $6); $3--;}; }
     | expr2 PLUS expr1	 	   					 { $$ = $1 + $3; }
     | expr2 MINUS expr1	   					 { $$ = $1 - $3; }
     | expr2 MULTIPLY expr1 	   					 { $$ = $1 * $3; }
     | expr2 DIVIDE expr1	  					 { $$ = $1 / $3; }
     | TPOW LSQ expr2 COMMA expr1 RSQ  					 { $$ = SMIpow($3, $5); }
     | TLOG LSQ expr2 COMMA expr1 RSQ  					 { $$ = SMIlog($3, $5); }
     | SAY LSQ expr2 LESS expr1 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3<$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 MORE expr1 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3>$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 LESSOR expr1 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3<=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 MOREOR expr1 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3>=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 EQUAL expr1 RSQ LSQ COM RSQ LSQ COM RSQ      	 { if($3==$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 NEQUAL expr1 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3!=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr2 LESS expr1 RSQ             			 { if($3<$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 MORE expr1 RSQ             			 { if($3>$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 LESSOR expr1 RSQ           			 { if($3<=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 MOREOR expr1 RSQ           			 { if($3>=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 EQUAL expr1 RSQ            			 { if($3==$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr2 NEQUAL expr1 RSQ           			 { if($3!=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | expr1 DIVIDE expr1 	   					 { $$ = $1 / (float)$3; }
     | expr1 REMAINDER expr1                    			 { $$ = $1 % $3; }
     | TPOW LSQ expr1 COMMA expr1 RSQ  					 { $$ = SMIpow($3, $5); }
     | TLOG LSQ expr1 COMMA expr1 RSQ  					 { $$ = SMIlog($3, $5); }
     | SAY LSQ expr1 LESS expr1 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3<$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 MORE expr1 RSQ LSQ COM RSQ LSQ COM RSQ       	 { if($3>$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 LESSOR expr1 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3<=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 MOREOR expr1 RSQ LSQ COM RSQ LSQ COM RSQ     	 { if($3>=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 EQUAL expr1 RSQ LSQ COM RSQ LSQ COM RSQ      	 { if($3==$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 NEQUAL expr1 RSQ LSQ COM RSQ LSQ COM RSQ      	 { if($3!=$5){printf("%s", $8); $$ = 1.0;}else{printf("%s", $11); $$ = 0.0;} }
     | SAY LSQ expr1 LESS expr1 RSQ             			 { if($3<$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 MORE expr1 RSQ             			 { if($3>$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 LESSOR expr1 RSQ           			 { if($3<=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 MOREOR expr1 RSQ          			         { if($3>=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 EQUAL expr1 RSQ           			         { if($3==$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | SAY LSQ expr1 NEQUAL expr1 RSQ           			 { if($3!=$5){printf("It really is!"); $$ = 1.0;}else{printf("Impudent lie! You can’t deceive me!"); $$ = 0.0;} }
     | CYCLE LSQ expr1 RSQ LSQ expr1 RSQ        			 { $$ = $3; while($3 > 0){printf("%i\n", $6); $3--;}; }
     | expr1 PLUS expr1		   					 { $$ = $1 + $3; }
     | expr1 MINUS expr1	   					 { $$ = $1 - $3; }
     | expr1 MULTIPLY expr1	   					 { $$ = $1 * $3; }
     | LB expr1 RB		   					 { $$ = $2; }
     | TFLOOR LSQ expr1 RSQ          					 { $$ = SMIfloor($3); }
     | TCEIL LSQ expr1 RSQ        					 { $$ = SMIceil($3); }
     | TROUND LSQ expr1 RSQ         					 { $$ = SMIround($3); }
     | TABS LSQ expr1 RSQ            					 { $$ = SMIabs($3); }
     | TFACT LSQ expr1 RSQ          					 { $$ = SMIfact($3); }
     | TLN LSQ expr1 RSQ          					 { $$ = SMIln($3); }
     | TEXP LSQ expr1 RSQ         					 { $$ = SMIexp($3); }
     | TSQRT LSQ expr1 RSQ         					 { $$ = SMIsqrt($3); }
     | TSIN LSQ expr1 RSQ       					 { $$ = SMIsin($3); }
     | TCOS LSQ expr1 RSQ       		 			 { $$ = SMIcos($3); }
     | TTG LSQ expr1 RSQ       						 { $$ = SMItg($3); }
     | TCTG LSQ expr1 RSQ      						 { $$ = SMIctg($3); }
     | CYCLE LSQ expr1 RSQ LSQ VARIABLE PLUS RSQ LSQ expr2 RSQ           { while($3>0){sym[$6] = sym[$6] + $10; printf("variable is %f\n", sym[$6]); $3--;} $$ = sym[$6]; }
     | CYCLE LSQ expr1 RSQ LSQ VARIABLE MINUS RSQ LSQ expr2 RSQ          { while($3>0){sym[$6] = sym[$6] - $10; printf("variable is %f\n", sym[$6]); $3--;} $$ = sym[$6]; }
     | CYCLE LSQ expr1 RSQ LSQ VARIABLE PLUS RSQ LSQ expr1 RSQ           { while($3>0){sym[$6] = sym[$6] + $10; printf("variable is %f\n", sym[$6]); $3--;} $$ = sym[$6]; }
     | CYCLE LSQ expr1 RSQ LSQ VARIABLE MINUS RSQ LSQ expr1 RSQ          { while($3>0){sym[$6] = sym[$6] - $10; printf("variable is %f\n", sym[$6]); $3--;} $$ = sym[$6]; }
;
expr1: INTNUMBER			     				 { $$ = $1; }
     | MINUS INTNUMBER                          			 { $$ = -$2; }
     | VARIABLE                                 			 { $$ = $1; }
;
%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
