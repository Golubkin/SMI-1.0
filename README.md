# SMI (Super-Mega-Interpreter)  
  
Lead: `Голубкин Николай`  
Developers: `Зинкин Станислав` и `Гугунов Сергей`  
  
Для компиляции используйте Makefile (который пока никто не сделал..):
```
$ make
```
или пишите вручную в Linux, следуя шагам:
```
$ bison -d parser.y
$ flex lexer.l
$ gcc parser.tab.c lex.yy.c -o smi -lm
$ ./smi
```
Для работы с SMI используйте команду:
```
$ hello
```
после чего интерпретатор сам всё расскажет о себе...
