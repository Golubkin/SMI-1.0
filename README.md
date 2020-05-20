# SMI (Super-Mega-Interpreter)  
  
Lead: `Голубкин Николай`  
Developers: `Зинкин Станислав` и `Гугунов Сергей`  
  
Для компиляции используйте CMake и Makefile:
```
$ cmake BUILD .
$ make
$ ./SMI
```
или пишите вручную в Linux, следуя шагам:
```
$ bison -d src/parser.y
$ flex src/lexer.l
$ gcc parser.tab.c lex.yy.c -o SMI -lm
$ ./SMI
```
Для работы с SMI используйте команду:
```
$ hello
```
после чего интерпретатор сам всё расскажет о себе...
