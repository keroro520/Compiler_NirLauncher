#include "builtin.h"
#include "init.h"
#include "environment.h"

void insertBuiltinNode(char * op, Node * (*f)(ListNode *, Env *) , Env * env) 
{
	updateEnv(env, newSymNode(str2Refer(op)), (Node *)(newBuiltinNode(f)));
}
void initBuiltinNode()
{
	insertBuiltinNode((char *)("+"), buiAdd, &top);
	insertBuiltinNode((char *)("-"), buiSub, &top);
	insertBuiltinNode((char *)("*"), buiMul, &top);
	insertBuiltinNode((char *)("/"), buiDiv, &top);
	insertBuiltinNode((char *)("quit"), buiQuit, &top);
}
