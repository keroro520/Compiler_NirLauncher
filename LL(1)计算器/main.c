#include <stdio.h>
#include "structure.h"
#include "parser.h"
#include "eval.h"
int main()
{
	Node * t = parser();
	printNode(t); puts("");
	printf("==> %d\n", eval(t)->val);
	return 0;
}
