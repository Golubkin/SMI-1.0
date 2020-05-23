%option noyywrap

%{
    #include <stdio.h>
    #define YY_DECL int yylex()
    #include "parser.hpp"
%}

%%

"hello"    {
                printf("Hello, my name is Super-Mega-Interpreter (SMI). Enter \"help\" to find out about my abilities!\n");
           }
"help"     {
		printf("\n------------------------------------------------------------------------------------------------------------------\n");
		printf("You can use standard operations like +, -, *, /, %%.\n\n");
                printf("You can use standard mathematical functions whose syntax is as follows: SMIsomefunc[arg] or SMIsomefunc[arg1, arg2].\n");
                printf("Function list:\n");
                printf("floor,\nceil,\nround,\nabs,\npow,\nsqrt,\nfact,\nsin,\ncos,\ntg,\nctg,\nexp,\nln,\nlog.\n\n");
                printf("You can use a command called \"say\" to find out whether you entered a true or false statement.\n");
  		printf("Syntax: say[\"statement\"]\n");
                printf("Inside you can use the following characters: >, <, >=, <=, =, !=\n\n");
                printf("You can use a command called \"cycle\" to use the cycle.\n");
 		printf("This cycle will output the specified number as many times as you specify.\n");
                printf("Syntax: cycle[\"int\"][\"int\"] or cycle[\"int\"][\"float\"]\n\n");
		printf("You can create variables. Syntax: \"letter\" = \"value\".\n\n");
		printf("To exit the program, enter \"exit\"\n");
		printf("\n------------------------------------------------------------------------------------------------------------------\n");
           }
[ \t]+     ;
[0-9]+                          { yylval.one = atoi(yytext); return (INTNUMBER); }
[0-9]+"."[0-9]+                 { yylval.two = atof(yytext); return (FLOATNUMBER); }
[a-z]                           { yylval.var = *yytext - 'a'; return (VARIABLE); }
\n                              { return (NEWLINE); }
"+"                             { return (PLUS); }
"-"                             { return (MINUS); }
"*"                             { return (MULTIPLY); }
"/"                             { return (DIVIDE); }
"%"                             { return (REMAINDER); }
"("                             { return (LB); }
")"                             { return (RB); }
"["                             { return (LSQ); }
"]"                             { return (RSQ); }
"<"                             { return (LESS); }
">"                             { return (MORE); }
"<="                            { return (LESSOR); }
">="                            { return (MOREOR); }
"!="                            { return (NEQUAL); }
"=="                            { return (EQUAL); }
"="                             { return (SETVALUE); }
","                             { return (COMMA); }
"exit"                          { return (EXIT); }
"SMIfloor"                      { return (TFLOOR); }
"SMIceil"                       { return (TCEIL); }
"SMIround"                      { return (TROUND); }
"SMIabs"                        { return (TABS); }
"SMIpow"                        { return (TPOW); }
"SMIsqrt"                       { return (TSQRT); }
"SMIfact"                       { return (TFACT); }
"SMIsin"                        { return (TSIN); }
"SMIcos"                        { return (TCOS); }
"SMItg"                         { return (TTG); }
"SMIctg"                        { return (TCTG); }
"SMIexp"                        { return (TEXP); }
"SMIln"                         { return (TLN); }
"SMIlog"                        { return (TLOG); }
"say"                           { return (SAY); }
"cycle"                         { return (CYCLE); }

%%
