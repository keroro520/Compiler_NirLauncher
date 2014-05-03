#include "builtin.h"
#include "init.h"
#include "environment.h"

extern ListNode nil;
extern Env top;
void insertBuiltinNode(char * op, Node * (*f)(ListNode *, Env *) , Env * env) 
{
	updateEnv(env, newSymNode(str2Refer(op)), (Node *)(newBuiltinNode(f)));
}
void initBuiltinNode()
{
	nil.type = LIST; nil.car = NULL; nil.cdr = NULL;
	top.father = NULL;

	insertBuiltinNode((char *)("+"), buiAdd, &top);
	insertBuiltinNode((char *)("-"), buiSub, &top);
	insertBuiltinNode((char *)("*"), buiMul, &top);
	insertBuiltinNode((char *)("/"), buiDiv, &top);
	insertBuiltinNode((char *)("type"), buiType, &top);
	insertBuiltinNode((char *)("quit"), buiQuit, &top);
	insertBuiltinNode((char *)("cons"), buiCons, &top);
	insertBuiltinNode((char *)("list"), buiList, &top);
	insertBuiltinNode((char *)("car") , buiCar , &top);
	insertBuiltinNode((char *)("cdr") , buiCdr , &top);
	insertBuiltinNode((char *)("null?"),buiNull, &top);
	insertBuiltinNode((char *)("begin") , buiBegin , &top);
	insertBuiltinNode((char *)("if") ,  buiIf  , &top);
	insertBuiltinNode((char *)("=") ,   buiEqu , &top);
	insertBuiltinNode((char *)("<") ,   buiGt  , &top);
	insertBuiltinNode((char *)(">") ,   buiLt  , &top);
	insertBuiltinNode((char *)("<=") ,  buiGE  , &top);
	insertBuiltinNode((char *)(">=") ,  buiLE  , &top);
}
