#include <stdio.h>

int yyparse();

int main() {
	 FILE* yyin = stdin;

	do {
		yyparse();
	} while(!feof(yyin));

	return 0;
}