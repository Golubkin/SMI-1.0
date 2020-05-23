# SMI (Super-Mega-Interpreter)  

![SMI](https://user-images.githubusercontent.com/55135260/82719267-a7685b00-9cb1-11ea-8a45-90eb949d086a.PNG)

Lead: `Голубкин Николай`  
Developers: `Зинкин Станислав` и `Гугунов Сергей`  

Для компиляции используйте CMake и Makefile:
```
$ cmake .
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
