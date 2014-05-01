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
	if ( eval((Node *)(args->cdr->car), env)->type == LIST ) {
		return (Node *) newListNode(eval(args->car, env), eval((Node *)(args->cdr->car), env));
	}
	return (Node *) cons(eval(args->car, env), eval(args->cdr->car, env));
}

Node * buiList(ListNode * args, Env * env)
{
	if (args == NULL) return NULL;
	ListNode * t = newListNode(eval(args->car, env), NULL), * s = t;
	for(args = args->cdr; args; args = args->cdr) {
		t = append(t, eval(args->car, env))->cdr;
	}
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
Node * buiQuit(ListNode* args, Env * env)
{
	exit(0);
}
Node * buiAdd(ListNode * args, Env * env)
{
	int ret = 0;
	Node * t;
	while(args) {
		if ((t = eval(args->car, env)) == NULL) {
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
		if ((t = eval(args->car, env)) == NULL) {
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
		if ((t = eval(args->car, env)) == NULL) {
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
		if ((t = eval(args->car, env)) == NULL) {
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
		if ((t = eval(args->car, env)) == NULL) {
			error("*** ERROR:+:\n Type \"number\" expected");
			exit(0);
		}
		if 		(t->type == NUMBER) ret /= toNum(t)->value;
		else if (t->type == SYMBOL) ret /= toNum(lookup(env, toSym(t)))->value;
		args = args->cdr;
	}
	return (Node *) newNumNode(ret);
}
