// 为什么不能在case下定义变量?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "eval.h"
#include "environment.h"

#define     error(s)        { fprintf(stderr, "%s\n", (s)); evalError = 1; }

extern Env top;
extern int evalError;

void evalInit()
{
	evalError = 0;
}
Node * reply(ProcNode * f, ListNode * args, Env * env) 
{
	if (len((Node *)(f->formal)) != len((Node *)args)) {
		error("*** ERROR:eval:\n Wrong number of arguments");
	}
	ProcNode * ff = NEW(ProcNode);								//实例化一个函数..比较低效
	memcpy(ff, f, sizeof (ProcNode));
	ff->env = NEW(Env);						//haha I find it   这里不新开一个Env的话会造成局部变量全局共享的情况!!!!
	memcpy(ff->env, f->env, sizeof(struct Env));
	ListNode * formal = ff->formal;
	for (int i = 0, length = len((Node *)formal); i < length; i++) {
		updateEnv(ff->env, toSym(formal->car), eval(args->car, env));
		formal = formal->cdr;
		args   = args->cdr;
	}
	Node * t = eval(ff->body, ff->env);
	return t;
}


Node * eval(Node * expr, Env * env) 
{
	if (evalError || !expr) return NULL;
	Node * f;
	Env * _env;
	switch (expr->type) {
		case NUMBER : case STR : case BOOL : case LIST : case ATOM : return expr;
		case SYMBOL : return lookup(env, toSym(expr)); 
		case PAIR   :
			return eval((Node *) newCallNode(toPair(expr)->car, (ListNode *) toPair(expr)->cdr), env);	//FIXME 
		case CALL   : 
			if (toCall(expr)->sym->type == SYMBOL) {									// (func (args))
				f = lookup(env, toSym(toCall(expr)->sym));					
				if (f->type == BUILTIN) {													// (builtin-func (args))
					return (toBui(f)->addr)(toCall(expr)->args, env);
				} 
			} else {																	// ( (procedure a func) (args) ) 未测
				f = eval(toCall(expr)->sym, env);
			}
			if (!f || f->type != PROC) {
				error("ERROR eval\nType \"procedure\" expected, \"bint\" provided ");
			}
			return reply(toProc(f), toCall(expr)->args, env);		//FIXME shi env 还是roProc(f)->env. 是env, toProc(f)会出现var not bound
		case LAMBDA :
			return (Node *) newProcNode(toLambda(expr)->formal, toLambda(expr)->body, env);
		case DEFINE :
			if (toDef(expr)->formal == NULL) {										// (define a xxx)
				updateEnv(&top, toDef(expr)->sym, eval(toDef(expr)->body, env));
			} else {
				_env = NEW(Env);
				memcpy(_env, env, sizeof (Env));
				updateEnv(&top, toDef(expr)->sym, (Node *) newProcNode(toDef(expr)->formal, toDef(expr)->body, _env));
				updateEnv(_env, toDef(expr)->sym, lookup(&top, toSym(toDef(expr)->sym)));
			}
			return lookup(&top, toDef(expr)->sym);
		default : return NULL;
	}
}
