#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"
#include "structure.h"
#include "lexer.h"
#include "eval.h"

extern int evalError;
extern ListNode nil;

PairNode * cons(Node * a,Node * b)
{
    PairNode * t = NEW(PairNode);
    t->type = PAIR;
    t->car  = a;
    t->cdr  = b;
    return t;
}
//a原本是list, 要拼接一个b上去, 如a = (1,2), 之后变成(1, 2, b), 注意cdr((1,2,b))的(2,b)也是List
ListNode * append(ListNode * a, Node * b)	
{
	ListNode * t = NEW(ListNode);
	t->type = LIST;
	t->car  = b;
	t->cdr  = &nil;
	a->cdr  = t; 

	return a;
}
Node * car(Node * a)
{
	if (a->type == LIST) return toList(a)->car;
    else 				 return toPair(a)->car;
}
Node * cdr(Node * a)
{
	if (a->type == LIST) return (Node *) (toList(a)->cdr);
    else 				 return toPair(a)->cdr;
}
int len(Node * a)
{
	if (a == NULL || a == (Node *)&nil) return 0;
	else if (a->type == LIST) return 1 + len((Node*)cdr(a));
	else if (a->type == PAIR) return 2;
	else return 1;
}


SymNode * newSymNode (Refer name) 
{
	SymNode * t = NEW(SymNode);
	t->type = SYMBOL;
	t->name = name;
	return t;
}

StrNode * newStrNode (Refer name)
{
	StrNode * t = NEW(StrNode);
	t->type = STR;
	t->name = name;
	return t;
}

BoolNode * newBoolNode (int value)
{
	BoolNode * t = NEW(BoolNode);
	t->type = BOOL;
	t->value = value;
	return t;
}

NumNode * newNumNode (int  value) 
{
	NumNode * t = NEW(NumNode);
	t->type  = NUMBER;
	t->value = value;
	return t;
}

PairNode * newPairNode(Node * a, Node * b)
{
	PairNode * t = NEW(PairNode);
	t->type = PAIR;
	t->car  = a;
	t->cdr  = b;
	return t;
}

ListNode * newListNode(Node * a, Node * b)		//a,b两个元素凑成一个list, 实际上会变成(a, b, '())
{
	ListNode * t = NEW(ListNode);
	t->type = LIST;
	t->car  = a ;

	ListNode * tt = NEW(ListNode);
	tt->type = LIST;
	tt->car  = b ;
	tt->cdr  = &nil;

	t->cdr = tt;
	return t;
}

LambdaNode* newLambdaNode(ListNode * formal, Node * body)
{
	LambdaNode * t = NEW(LambdaNode);
	t->type   = LAMBDA;
	t->formal = formal;
	t->body   = body;
	return t;
}
DefNode* newDefNode(SymNode * sym, ListNode * formal, Node * body)
{
	if (top.sym[sym->name] && top.sym[sym->name]->type == BUILTIN) {
		fprintf(stderr, "*** ERROR:define: read-only variable");
		evalError = 1;
		return NULL;
	}
	DefNode * t = NEW(DefNode);
	t->type   = DEFINE;
	t->sym    = sym;
	t->formal = formal;
	t->body   = body;
	return t;
}
CallNode* newCallNode(Node * sym, ListNode * args)
{
	CallNode * t = NEW(CallNode);
	t->type = CALL;
	t->sym  = sym;
	t->args = args;
	return t;
}

ProcNode* newProcNode(ListNode * formal, Node * body, Env * env) 
{
	ProcNode * t = NEW(ProcNode);
	t->type = PROC;
	t->formal = formal;
	t->body   = body;
	t->env    = env;
	return t;
}

BuiltinNode * newBuiltinNode(Node * (*addr)(ListNode *, Env *))
{
	BuiltinNode * t = NEW(BuiltinNode);
	t->type = BUILTIN;
	t->addr = addr;
	return t;
}

AtomNode * newAtomNode(Refer name)
{
	AtomNode * t = NEW(AtomNode);
	t->type = ATOM;
	t->name = name;
	return t;
}

void printNode(Node * a)
{
	static int startOfList = 1;
	if (a == NULL) return ;
	switch (a->type) {
		case SYMBOL : printf("%s", refer2Str(toSym(a)->name)); 	  break;
		case STR    : printf("%s", refer2Str(toStr(a)->name)); 	  break;
		case NUMBER : printf("%d", toNum(a)->value); 			  break;
		case ATOM	: printf("\'%s", refer2Str(toAtom(a)->name)); break;
		case BOOL	: printf("#%c",toBool(a)->value == 0 ? 'f' : 't'); break;
		case LIST   : 
			if (a == (Node *) &nil) {
				printf("()"); 
				break; 
			}
			if (startOfList) printf("(");
			startOfList = 1;
			printNode(car(a));
			startOfList = 0;

			if (toList(a)->cdr == &nil) printf(")");
			else printf(" "), printNode(cdr(a));
			startOfList = 1;
			break;
		case PAIR   :
			printf("(");
			printNode(car(a));
			printf(" . ");
			printNode(cdr(a));
			printf(")");
			break;
		case PROC   :
			printf("#<procedure :>" );
		default : ;
	}
}

Refer str2Refer(char * s)
{
	int i;
	for (i = 0; i < 1984 && strTable[i]; i++) {
		if (strcmp(strTable[i], s) == 0) return i;
	}
	if (i >= 1984) {
		fprintf(stderr, "Out of space");
		exit(0);
	}
	strTable[i] = malloc((sizeof (char)) * (1 + strlen(s)));
	strcpy(strTable[i], s);
	return i;
}

char * refer2Str(Refer i)
{
	return strTable[i];
}

int refer2Num(Refer i)
{
	char * s = strTable[i];
	int x = 0;
	while(*s) {
		x = x * 10 + (*s - '0') ;
		s++;
	}
	return x;
}
