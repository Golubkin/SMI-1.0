//Bison-файл.

%token OR AND NOT EQUAL PLUS MINUS MULITPLY DIVIDE INTNUMBER FLOATNUMBER REMAINDER POW LEFTBR RIGHTBR
%right EQUAL
%left OR
%left AND
%left NOT
%left PLUS MINUS
%left MULTIPLY DIVIDE REMAINDER

%{
      #include <iostream>
      using namespace std;
%}

%%
//Определение наборов правил для анализа
// Сделать приоритет.
AddOrSub: NUMBER PLUS NUMBER
          {
                cout << $1 + $3 << endl;
          }
          |  NUMBER MINUS NUMBER
          {
                cout << $1 - $3 << endl;
          }
          ;
MultOrDiv: NUMBER MULTIPLY NUMBER
           {
                cout << $1 * $3 << endl;
           }
           | NUMBER DIVIDE NUMBER
           {
                cout << $1 / $3 << endl;
           }
           ;

%%

//Дополнительный исходный код С++
