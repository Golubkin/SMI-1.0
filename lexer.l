// Flex-файл.

%{
#include <iostream>
#include "y.tab.h"
using namespace std;
// добавить main func 
%}

%%
hello      {
                cout << "Hello, My name is Super-Mega-Interpreter (SMI). Enter "help" to find out about my abilities!" << endl;
           }
help       {
                // будет показывать доступные команды
           }
.          {//перенести потом в конец.
                cout << "Syntax error" << endl;
           }
[ \t\n]+   {
                //Игнорирование пробелов, табуляции и пустых строк.
           }
("+"|"-")?[1-9][0-9]*           return INTNUMBER; // Токен.
("+"|"-")?[0-9]+"."[0-9]+       return FLOATNUMBER;
"="                             return EQUAL;
"+"                             return PLUS;
"-"                             return MINUS;
"*"                             return MULTIPLY;
"/"                             return DIVIDE;
"%"                             return REMAINDER;
"**"                            return POW;
"("                             return LEFTBR;
")"                             return RIGHTBR;

%%

int main()
{
    yylex();
}
