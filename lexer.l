// Flex-файл.

%{

%}

%%
"hello"    {
                printf("Hello, My name is Super-Mega-Interpreter (SMI). Enter \"help\" to find out about my abilities!");
           }
"help"     {
                // будет показывать доступные команды
           }
.          {//перенести потом в конец.
                printf("Syntax error");
           }
[ \t]+     {
                //Игнорирование пробелов и табуляции.
           }
("+"|"-")?[1-9][0-9]*           return (INTNUMBER); // Токен.
("+"|"-")?[0-9]+"."[0-9]+       return (FLOATNUMBER);
"="                             return (EQUAL);
"+"                             return (PLUS);
"-"                             return (MINUS);
"*"                             return (MULTIPLY);
"/"                             return (DIVIDE);
"%"                             return (REMAINDER);
"("                             return (LB);
")"                             return (RB);
","                             return (COMMA);
"#"                             return (COMMENT);
"and"                           return (AND);
"or"                            return (OR);
"not"                           return (NOT);
"floorSMI"                      return (TFLOOR);
"ceilSMI"                       return (TCEIL);
"roundSMI"                      return (TROUND);
"absSMI"                        return (TABC);
"powSMI"                        return (TPOW);
"sqrtSMI"                       return (TSQRT);
"factSMI"                       return (TFACT);
"sinSMI"                        return (TSIN);
"cosSMI"                        return (TCOS);
"tgSMI"                         return (TTG);
"expSMI"                        return (TEXP);
"lnSMI"                         return (TLN);
"logSMI"                        return (TLOG);
"if"                            return (IF);
"else"                          return (ELSE);
"while"                         return (WHILE);
"for"                           return (FOR);

%%

int main()
{
    yylex();
}
