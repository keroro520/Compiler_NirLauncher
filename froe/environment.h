#ifndef 	__ENVIRONMENT_H__
#define		__ENVIRONMENT_H__

#include <stdio.h>
#include "structure.h"

typedef struct Env {
	Node * sym[1984];
	struct Env * father;
} Env;

Node * lookup(Env * env, SymNode * sym) ;
void updateEnv(Env * env, SymNode * sym, Node * value) ;

Env top ;

#endif
