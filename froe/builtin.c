#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "builtin.h"
#define			error(s)		fprintf(stderr, "%s", (s))

Node * buiCons(ListNode * args, Env * env)
{
	if (len((Node *)args) != 2) {
		error("*** ERROR:eval:\n Wrong number of arguments: 2 expected        cons");
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
	for(args = args->cdr; args; args = args->cdr) {
		t = append(t, eval(args->car, env))->cdr;
	}
	t->cdr = &nil;
	return (Node *) s;
}

Node * buiCar (ListNode * args, Env * env)
{
	if (len((Node *) args) != 1) {
		error("** ERROR:eval:\n Wrong number of arguments: 1 expected          car");
		exit(0);
	}
	Node * t = eval(args->car, env);
	if (t->type != PAIR) {
		return toPair(t)->car;
	} else if (t->type != LIST) {
		return toList(t)->car;	
	} else {
		error("*** ERROR:car:\n Type \"pair\" expected  				car");
		exit(0);
	}
}
Node * buiCdr (ListNode * args, Env * env)
{
	if (len((Node *) args) != 1) {
		error("** ERROR:eval:\n Wrong number of arguments: 1 expected          car");
		exit(0);
	}
	Node * t = eval(args->car, env);
	if (t->type != PAIR) {
		return toPair(t)->cdr;
	} else if (t->type != LIST) {
		return (Node *) (toList(t)->car);
	} else {
		error("*** ERROR:car:\n Type \"pair\" expected  				cdr");
		exit(0);
	}
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
		error("** ERROR:eval:\n Wrong number of arguments: 1 expected          type");
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
	while(args) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:+:\n Type \"number\" expected");
			exit(0);
		}
		if 		(t->type == NUMBER) ret += toNum(t)->value;
		else if (t->type == SYMBOL) ret += toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
Node * buiSub(ListNode * args, Env * env)
{
	int ret = 0;
	Node * t;
	while(args) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:+:\n Type \"number\" expected");
			exit(0);
		}
		if 		(t->type == NUMBER) ret -= toNum(t)->value;
		else if (t->type == SYMBOL) ret -= toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
Node * buiMul(ListNode * args, Env * env)
{
	int ret = 1;
	Node * t;
	while(args) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:+:\n Type \"number\" expected");
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
			error("*** ERROR:+:\n Type \"number\" expected");
			exit(0);
		} else if (t->type == NUMBER) ret = toNum(t)->value;
		  else if (t->type == SYMBOL) ret = toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	} else if (args == NULL) {
		error("*** ERROR:eval:\n Wrong number of arguments: -2 expected, 0 provided");
		exit(0);
	}
	while(args) {
		if ((t = eval(args->car, env)) == NULL || (t->type != NUMBER && t->type != SYMBOL)) {
			error("*** ERROR:+:\n Type \"number\" expected");
			exit(0);
		}
		if 		(t->type == NUMBER) ret /= toNum(t)->value;
		else if (t->type == SYMBOL) ret /= toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
