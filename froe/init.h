#ifndef			__INIT_H__
#define			__INIT_H__
#include "structure.h"

void insertBuiltinNode(char * op, Node * (*f)(ListNode *, Env *) , Env * env) ;
void initBuiltinNode() ;

#endif
