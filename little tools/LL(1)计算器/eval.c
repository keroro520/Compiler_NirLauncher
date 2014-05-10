#include <stdio.h>
#include <ctype.h>
#include "eval.h"

NumNode * eval(Node * a)
{
	switch (a->type) {
		case E  : return Eeval(a);
		case E1 : return E1eval(a);
		case T  : return Teval(a);
		case T1 : return T1eval(a);
		case F  : return Feval(a);
		default : return TerminalEval(a);
	}
}

NumNode * Eeval(Node * a)
{
	NumNode * x = eval(a->child);
	Node * child = a->child->brother->child;
	if (child == NULL) {											//E -> T
		return x;
	} else if (toTer(child)->ctx == str2Refer("+")) {				//E -> TE1 -> T + TE1
		return newNumNode(x->val + eval(a->child->brother)->val);
	} else if (toTer(child)->ctx == str2Refer("-")) {				//E -> TE1 -> T - TE1
		return newNumNode(x->val + eval(a->child->brother)->val);
	}
	return NULL;
}
NumNode * E1eval(Node * a)
{
	Node * child = a->child->brother;
	NumNode * x = eval(child);
	child = child->brother->child;
	if (child == NULL) {
		return x;
	} else if (toTer(child)->ctx == str2Refer("+")) {
		return newNumNode(x->val + eval(a->child->brother->brother)->val);
	} else if (toTer(child)->ctx == str2Refer("-")) {
		return newNumNode(x->val - eval(a->child->brother->brother)->val);
	}
	return NULL;
}
NumNode * Teval(Node * a)
{
	NumNode * x = eval(a->child);
	Node * child = a->child->brother->child;
	if (child == NULL) {
		return x;
	} else if (toTer(child)->ctx == str2Refer("*")) {
		return newNumNode(x->val * eval(a->child->brother)->val);
	} else if (toTer(child)->ctx == str2Refer("/")) {
		return newNumNode(x->val / eval(a->child->brother)->val);
	}
	return NULL;
}
NumNode * T1eval(Node * a)
{
	Node * child = a->child->brother;
	NumNode * x = eval(child);
	child = child->brother->child;
	if (child == NULL) {
		return x;
	} else if (toTer(child)->ctx == str2Refer("*")) {
		return newNumNode(x->val * eval(a->child->brother->brother)->val);
	} else if (toTer(child)->ctx == str2Refer("/")) {
		return newNumNode(x->val / eval(a->child->brother->brother)->val);
	}
	return NULL;
}
NumNode * Feval(Node * a)
{
	Node * child = a->child;
	if (toTer(child)->ctx == str2Refer("(")) {
		return eval(child->brother);
	} else if (child->type == TERMINAL) {
		return TerminalEval(child);
	} 
	return NULL;
}
NumNode * TerminalEval(Node * a)
{
	char * s = refer2Str(toTer(a)->ctx);
	if (isdigit(s[0])) return newNumNode(stoi(s));
	return NULL; 													//FIXME
}
