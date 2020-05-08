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
"-"?[1-9][0-9]*           { yylval.one = atoi(yytext); return (INTNUMBER); }
"-"?[0-9]+"."[0-9]+       { yylval.two = atof(yytext); return (FLOATNUMBER); }
\n                              { return (NEWLINE); }
"+"                             { return (PLUS); }
"-"                             { return (MINUS); }
"*"                             { return (MULTIPLY); }
"/"                             { return (DIVIDE); }
"%"                             { return (REMAINDER); }
"("                             { return (LB); }
")"                             { return (RB); }
","                             { return (COMMA); }
"#"                             { return (COMMENT); }
"<"                             { return (LC); }
">"                             { return (RC); }
"exit"                          { return (EXIT); }
"and"                           { return (AND); }
"or"                            { return (OR); }
"not"                           { return (NOT); }
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
"if"                            { return (IF); }
"then"                          { return (THEN); }
"else"                          { return (ELSE); }
"while"                         { return (WHILE); }
"for"                           { return (FOR); }

%%
