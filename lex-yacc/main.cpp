#include <stdio.h>
//#include "lex.yy.c"
int yywrap() {
	return 1;
}
int main()
{
	yylex();
	printf("hello world !\n");

	return 0;
}
