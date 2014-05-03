#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "builtin.h"
#define			error(s)		fprintf(stderr, "%s", (s))

int getValue(Node * a, Env * env) ;

Node * buiCons(ListNode * args, Env * env)
{
	if (len((Node *)args) != 2) {
		error("*** ERROR:cons:\n Wrong number of arguments: 2 expected        cons");
		exit(0);
	}
	Node * t = eval((Node *)(args->cdr->car), env);
	if ( t->type == LIST ) {
		ListNode * tt = NEW(ListNode);
		tt->type= LIST;
		tt->car = eval(args->car, env);
		tt->cdr = toList(t);
		return (Node *)tt;
	}
	return (Node *) cons(eval(args->car, env), eval(args->cdr->car, env));
}

Node * buiList(ListNode * args, Env * env)
{
	if (args->car == NULL) return (Node *) &nil;
	ListNode * t = newListNode(eval(args->car, env), (Node *)&nil), * s = t;
	for(args = args->cdr; args && args != &nil; args = args->cdr) {
		t = append(t, eval(args->car, env))->cdr;
	}
	t->cdr = &nil;
	return (Node *) s;
}

Node * buiCar (ListNode * args, Env * env)
{
	Node * t = eval(args->car, env);					// 比如(list 1) 其实我表示成了(list 1 '())   =_=   自己栽在自己手上了..
	if (len(t) != 1) {
		error("** ERROR:car :\n Wrong number of arguments: 1 expected          car");
		exit(0);
	}
	if (t->type != PAIR) {
		return eval(toPair(t)->car, env);
	} else if (t->type != LIST && t != (Node *) &nil) {
		return eval(toList(t)->car, env);
	} else {
		error("*** ERROR:car:\n Type \"pair\" expected  				car");
		exit(0);
	}
}
Node * buiCdr (ListNode * args, Env * env)
{
	Node * t = eval((args->car), env);
	if (len(t) != 1) {
		error("** ERROR:cdr :\n Wrong number of arguments: 1 expected          cdr");
		exit(0);
	}
	if (t->type != PAIR) {
		return eval(toPair(t)->cdr, env);
	} else if (t->type != LIST && t != (Node *) &nil) {
		return eval((Node *)toList(t)->cdr, env);
	} else {
		error("*** ERROR:cdr:\n Type \"pair\" expected  				cdr");
		exit(0);
	}
}

Node * buiNull(ListNode * args, Env * env)
{
	if (len((Node *) args) != 1) {
		error("*** ERROR:null?:\n Wrong number of arguments: 1 expected") ;
		exit(0);
	}
	Node * t = eval(args->car, env); 
	return (t == NULL || t == (Node *) &nil) ? (Node *) newBoolNode(1) : (Node *) newBoolNode(0) ;
}
Node * buiIf(ListNode * args, Env * env)
{
	if (len((Node *) args) < 2 || len((Node *) args) > 3) {
		error("*** ERROR:if:\n Illegal form");
		exit(0);
	}
	Node * t = eval(args->car, env);
	if (t->type == BOOL && toBool(t)->value == 0) return eval(args->cddar, env);
	else					  					  return eval(args->cdar, env);
}

Node * buiBegin (ListNode * args, Env * env) 
{
	Node * t = NULL;
	while (args) {
		t = eval(args->car, env);
		args = args->cdr;
	}
	return t;
}

Node * buiType(ListNode * args, Env * env)
{
	if (len((Node *) args) != 1) {
		error("** ERROR:type:\n Wrong number of arguments: 1 expected          type");
		exit(0);
	}
		
	Node * t = eval((Node *) (args->car), env);
	switch (t->type) {
		case SYMBOL	: 	printf("type \"%s\"", "symbol"); break;
		case NUMBER	: 	printf("type \"%s\"", "number"); break;
		case STR	: 	printf("type \"%s\"", "string"); break;
		case LAMBDA	: 	printf("type \"%s\"", "lambda"); break;
		case PROC	: 	printf("type \"%s\"", "procedure"); 		break;
		case BUILTIN: 	printf("type \"%s\"", "builtin procedure"); break;
		case LIST	: 	printf("type \"%s\"", "list"); 	 break;
		case PAIR	: 	printf("type \"%s\"", "pair"); 	 break;
		case ATOM   : 	printf("type \"%s\"", "atom");   break;
		case BOOL	:	printf("type \"%s\"", "bool");	 break;
		default 	: ;
	}
	return NULL;
}

Node * buiQuit(ListNode * args, Env * env)
{
	exit(0);
}
Node * buiAdd(ListNode * args, Env * env)
{
	int ret = 0;
	Node * t;
	while(args != &nil) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:+:\n Type \"number\" expected");
			exit(0);
		}
		ret += getValue(t, env);
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
Node * buiSub(ListNode * args, Env * env)
{
	int ret = 0;
	Node * t;

	if (len((Node *) args) < 2) {
		error("*** ERROR:sub:\n Wrong number of arguments: -2 expected");
		exit(0);
	}
	if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
		error("*** ERROR:-:\n Type \"number\" expected");
		exit(0);
	}

	ret = getValue(t, env);
	args = args->cdr;

	while(args != &nil) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:-:\n Type \"number\" expected");
			exit(0);
		}
		ret -= getValue(t, env);
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
Node * buiMul(ListNode * args, Env * env)
{
	int ret = 1;
	Node * t;
	while(args != &nil) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:*:\n Type \"number\" expected");
			exit(0);
		}
		if 		(t->type == NUMBER) ret *= toNum(t)->value;
		else if (t->type == SYMBOL) ret *= toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
Node * buiDiv(ListNode * args, Env * env)
{
	Node * t;
	int ret = 1;
	if (len((Node *)args) >= 2) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:/:\n Type \"number\" expected");
			exit(0);
		} else if (t->type == NUMBER) ret = toNum(t)->value;
		  else if (t->type == SYMBOL) ret = toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	} else if (args == &nil) {
		error("*** ERROR:/:\n Wrong number of arguments: -2 expected, 0 provided");
		exit(0);
	}
	while(args != &nil) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:/:\n Type \"number\" expected");
			exit(0);
		}
		if 		(t->type == NUMBER) ret /= toNum(t)->value;
		else if (t->type == SYMBOL) ret /= toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}

int getValue(Node * a, Env * env)
{
	if (a->type == NUMBER) return toNum(a)->value;
	else if (a->type == SYMBOL) {
		Node * t = lookup(env, toSym(a));
		if (t->type == NUMBER) return toNum(t)->value;
	}
	error("*** ERROR:getValue:\n Type \"number\" expected");
	exit(0);
}
Node * buiEqu(ListNode * args, Env * env)
{
	if (len((Node *) args) < 2) {
		error("*** ERROR:=:\n Wrong number of arguments: -at least 2 expected");
		exit(0);
	}
	int value = getValue(eval(args->car, env), env);
	for (ListNode * it = args; it != &nil; it = it->cdr) {
		getValue(eval(it->car, env), env);
	}
	for (ListNode * it = args->cdr; it != &nil; it = it->cdr) {
		if (getValue(eval(it->car, env), env) != value) return (Node *) newBoolNode(0);
	}
	return (Node *) newBoolNode(1);
}
Node * buiGt(ListNode * args, Env * env)
{
	if (len((Node *) args) < 2) {
		error("*** ERROR:<:\n Wrong number of arguments: -at least 2 expected");
		exit(0);
	}
	int value = getValue(eval(args->car, env), env), t;
	for (ListNode * it = args; it != &nil; it = it->cdr) {
		getValue(eval(it->car, env), env);
	}
	for (ListNode * it = args->cdr; it != &nil; it = it->cdr) {
		if ((t = getValue(eval(it->car, env), env)) <= value) return (Node *) newBoolNode(0);
		value = t;
	}
	return (Node *) newBoolNode(1);
}
Node * buiLt(ListNode * args, Env * env)
{
	if (len((Node *) args) < 2) {
		error("*** ERROR:>:\n Wrong number of arguments: -at least 2 expected");
		exit(0);
	}
	int value = getValue(eval(args->car, env), env), t;
	for (ListNode * it = args; it != &nil; it = it->cdr) {
		getValue(eval(it->car, env), env);
	}
	for (ListNode * it = args->cdr; it != &nil; it = it->cdr) {
		if ((t = getValue(eval(it->car, env), env)) >= value) return (Node *) newBoolNode(0);
		value = t;
	}
	return (Node *) newBoolNode(1);
}
Node * buiGE(ListNode * args, Env * env)
{
	if (len((Node *) args) < 2) {
		error("*** ERROR:<=:\n Wrong number of arguments: -at least 2 expected");
		exit(0);
	}
	int value = getValue(eval(args->car, env), env), t;
	for (ListNode * it = args; it != &nil; it = it->cdr) {
		getValue(eval(it->car, env), env);
	}
	for (ListNode * it = args->cdr; it != &nil; it = it->cdr) {
		if ((t = getValue(eval(it->car, env), env)) < value) return (Node *) newBoolNode(0);
		value = t;
	}
	return (Node *) newBoolNode(1);
}
Node * buiLE(ListNode * args, Env * env)
{
	if (len((Node *) args) < 2) {
		error("*** ERROR:>=:\n Wrong number of arguments: -at least 2 expected");
		exit(0);
	}
	int value = getValue(eval(args->car, env), env), t;
	for (ListNode * it = args; it != &nil; it = it->cdr) {
		getValue(eval(it->car, env), env);
	}
	for (ListNode * it = args->cdr; it != &nil; it = it->cdr) {
		if ((t = getValue(eval(it->car, env), env)) > value) return (Node *) newBoolNode(0);
		value = t;
	}
	return (Node *) newBoolNode(1);
}
