#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"

extern char * strTable[1984];

Node * newNode(NodeType type)
{
	Node * t = NEW(Node);
	t->type = type;
	return t;
}
NumNode * newNumNode(int val)
{
	NumNode * t = NEW(NumNode);
	t->type = TERMINAL;
	t->val  = val;
	return t;
}
TerminalNode * newTerminalNode(Refer ctx)
{
	TerminalNode * t = NEW(TerminalNode);
	t->type = TERMINAL;
	t->ctx  = ctx;
	return t;
}
void printNode(Node * a)
{
	if (a == NULL) return ;
	switch (a->type) {
		case TERMINAL :
			printNode(a->child);
			printf("%s", refer2Str(toTer(a)->ctx));
			printNode(a->brother);
			break;
		default :
			printNode(a->child);
			printNode(a->brother);
	}
}

Refer str2Refer(char * s)
{
	int i;
	for (i = 0; strTable[i]; i++) {
		if (strcmp(s, strTable[i]) == 0) return i ;
	}
	if (i >= 1984) {
		fprintf(stderr, "Out of space");
		exit(0);
	}

	strTable[i] = malloc(sizeof (char) * (1 + strlen(s)));
	strcpy(strTable[i], s);
	return i;
}

char * refer2Str(Refer i)
{
	return strTable[i];
}

int stoi(char * s)
{
	int t = 0;
	while(*s) {
		t = t * 10 + (*s - '0');
		s++;
	}
	return t;
}
