#ifndef 	__EVAL_H__
#define		__EVAL_H__
#include "structure.h"

Node * reply(ProcNode * f, ListNode * args, Env * env) ;
Node * eval(Node * expr, Env * env) ;
void evalInit() ;

int evalError ;
#endif
