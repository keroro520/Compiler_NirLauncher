#include <stdio.h>
#include "structure.h"
#include "environment.h"
#include "parser.h"
#include "eval.h"
#include "lexer.h"
#include "init.h"

extern int evalError ;
int main()
{
	initBuiltinNode();

	Node * t;
	while(1) {
		printf(">> ");
		evalInit();
		Node * a = parser();
		if (a == NULL && evalError == 0) break;			//有时候parser()出错会返回NULL

		t = eval(a, &top);
		printNode( t );
		puts("");
	}
	return 0;
}
