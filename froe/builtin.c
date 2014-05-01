#include <stdio.h>
#include <stdlib.h>
#include "eval.h"
#include "builtin.h"
#define			error(s)		fprintf(stderr, "%s", (s))

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
