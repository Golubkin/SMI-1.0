//Bison-файл.

%{
      #include <iostream>
      using namespace std;
%}

// описания (дополнительные определения токенов)

%%
//Определение наборов правил для анализа
// Сделать приоритет.
AddOrSub: NUMBER PLUS NUMBER
          {
                cout << $1 + $2 << endl;
          }
          |  NUMBER MINUS NUMBER
          {
                cout << $1 - $2 << endl;
          }
          ;
MultOrDiv: NUMBER MULTIPLY NUMBER
           {
                cout << $1 * $2 << endl;
           }
           | NUMBER DIVIDE NUMBER
           {
                cout << $1 / $2 << endl;
           }
           ;

%%

//Дополнительный исходный код С++
