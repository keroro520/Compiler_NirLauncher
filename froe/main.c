#include <stdio.h>
#include "structure.h"
#include "environment.h"
#include "parser.h"
#include "eval.h"
#include "lexer.h"
#include "init.h"

int main()
{
	initBuiltinNode();

	Node * t;
	while(1) {
		printf(">> ");
		Node * a = parser();
		if (a == NULL) break;
		t = eval(a, &top);
		printNode( t );
		puts("");
	}
	return 0;
}
