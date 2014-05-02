// 为什么不能在case下定义变量?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "eval.h"
#include "environment.h"

#define     error(s)        fprintf(stderr, "%s\n", (s))

extern Env top;

Node * reply(ProcNode * f, ListNode * args, Env * env) 
{
	if (len((Node *)(f->formal)) != len((Node *)args)) {
		error("*** ERROR:eval:\n Wrong number of arguments");
		exit(0);
	}

	ProcNode * ff = NEW(ProcNode);								//实例化一个函数..比较低效
	memcpy(ff, f, sizeof (ProcNode));
	ListNode * formal = ff->formal;
	for (int i = 0, length = len((Node *)formal); i < length; i++) {
		updateEnv(ff->env, toSym(formal->car), args->car);
		formal = formal->cdr;
		args   = args->cdr;
	}
	Node * t = eval(ff->body, ff->env);
	return t;
}


Node * eval(Node * expr, Env * env) 
{
	if (!expr) return NULL;
	Node * f;
	Env * _env;
	switch (expr->type) {
		case NUMBER : case STR : case BOOL : case LIST : case ATOM : return expr;
		case SYMBOL : return lookup(env, toSym(expr));
		case PAIR   :
			return eval((Node *) newCallNode(toPair(expr)->car, (ListNode *) toPair(expr)->cdr), env);
		case CALL   : 
			if (toCall(expr)->sym->type == SYMBOL) {									// (func (args))
				f = lookup(env, toSym(toCall(expr)->sym));					
				if (f->type == BUILTIN) {													// (builtin-func (args))
					return (toBui(f)->addr)(toCall(expr)->args, env);
				}
			} else {																	// ( (procedure a func) (args) )
				f = eval(toCall(expr)->sym, env);
			}
			if (!f || f->type != PROC) {
				error("ERROR eval\nType \"procedure\" expected, \"bint\" provided ");
				exit(0);
			}
			return reply(toProc(f), toCall(expr)->args, env);
		case LAMBDA :
			return (Node *) newProcNode(toLambda(expr)->formal, toLambda(expr)->body, env);
		case DEFINE :
			if (toDef(expr)->formal == NULL) {										// (define a xxx)
				updateEnv(&top, toDef(expr)->sym, eval(toDef(expr)->body, env));
			} else {
				_env = NEW(Env);
				memcpy(_env, env, sizeof (Env));
				updateEnv(&top, toDef(expr)->sym, (Node *) newProcNode(toDef(expr)->formal, toDef(expr)->body, _env));
			}
			return NULL;
		default : error("I think No Default"); exit(0);
	}
}
