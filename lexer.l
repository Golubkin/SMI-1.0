/* Опция noyywrap указывает, что входной текст один, и после чтения EOF не нужно пытаться перейти к следующему тексту. */
%option noyywrap

%{
    #include <stdio.h>
    #define YY_DECL int yylex()
    #include "parser.tab.h"
%}

%%

"hello"    {
                printf("Hello, my name is Super-Mega-Interpreter (SMI). Enter \"help\" to find out about my abilities!\n");
           }
"help"     {
               
           }
[ \t]+     ;
("+"|"-")?[1-9][0-9]*           { yylval.one = atoi(yytext); return (INTNUMBER); }
("+"|"-")?[0-9]+"."[0-9]+       { yylval.two = atof(yytext); return (FLOATNUMBER); }
\n                              { return (NEWLINE); }
"="                             { return (EQUAL); }
"+"                             { return (PLUS); }
"-"                             { return (MINUS); }
"*"                             { return (MULTIPLY); }
"/"                             { return (DIVIDE); }
"%"                             { return (REMAINDER); }
"("                             { return (LB); }
")"                             { return (RB); }
","                             { return (COMMA); }
"#"                             { return (COMMENT); }
"exit"                          { return (EXIT); }
"and"                           { return (AND); }
"or"                            { return (OR); }
"not"                           { return (NOT); }
"floorSMI"                      { return (TFLOOR); }
"ceilSMI"                       { return (TCEIL); }
"roundSMI"                      { return (TROUND); }
"absSMI"                        { return (TABC); }
"powSMI"                        { return (TPOW); }
"sqrtSMI"                       { return (TSQRT); }
"factSMI"                       { return (TFACT); }
"sinSMI"                        { return (TSIN); }
"cosSMI"                        { return (TCOS); }
"tgSMI"                         { return (TTG); }
"expSMI"                        { return (TEXP);}
"lnSMI"                         { return (TLN); }
"logSMI"                        { return (TLOG); }
"if"                            { return (IF); }
"else"                          { return (ELSE); }
"while"                         { return (WHILE); }
"for"                           { return (FOR); }

%%
