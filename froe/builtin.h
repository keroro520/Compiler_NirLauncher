#ifndef		__BUILTIN_H__
#define		__BUILTIN_H__

#include "structure.h"
#include "environment.h"

Node * buiCons(ListNode * args, Env * env) ;
Node * buiList(ListNode * args, Env * env) ;
Node * buiCar (ListNode * args, Env * env) ;
Node * buiCdr (ListNode * args, Env * env) ;

Node * buiAdd(ListNode *  args, Env * env) ;
Node * buiSub(ListNode *  args, Env * env) ;
Node * buiMul(ListNode *  args, Env * env) ;
Node * buiDiv(ListNode *  args, Env * env) ;

Node * buiIf  (ListNode * args, Env * env) ;
Node * buiBegin (ListNode * args, Env * env) ;
Node * buiSet (ListNode * args, Env * env) ;
Node * buiType(ListNode * args, Env * env) ;
Node * buiQuit(ListNode * args, Env * env) ;

Node * buiEqu(ListNode * args, Env * env)  ;
#endif
