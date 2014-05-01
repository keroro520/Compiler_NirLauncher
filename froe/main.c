#include <stdio.h>
#include "structure.h"
#include "environment.h"
#include "parser.h"
#include "eval.h"
#include "lexer.h"
int main()
{
	while(1) {
		Node * a = parser();
		if (a == NULL) break;
		printNode(a);
		printf("   ===   ");
		printNode(eval(a, &top)); 
		puts("");
	}
	return 0;
}
