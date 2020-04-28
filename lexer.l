// Flex-файл.

// char* yytext - переменная, хранящая строку из C++ (С \0 в конце), которая является текущим найденным шаблоном. 
// int yyleng - переменная, хранящая длину этой строки.
// yylex() - ф-я, содержащая все действия, описанные в Flex-файле (секция правил). Нужно добавить в main().
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
