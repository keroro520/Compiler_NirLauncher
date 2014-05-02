#include <stdlib.h>
#include "environment.h"
#include "structure.h"

#define		error(s)		fprintf(stderr, "%s\n", (s))
Env top = {.father = NULL} ;
Node * lookup(Env * env, SymNode * sym)
{
	Refer i = sym->name;
	do {
		if (env->sym[i] != NULL) return env->sym[i];
		env = env->father;
	} while (env) ;
	printf("!! %s !!\n", refer2Str(sym->name));
	error("*** ERROR:lookup:\nUnbound variable");
	exit(0);
}
void updateEnv(Env * env, SymNode * sym, Node * value) 
{
	env->sym[sym->name] = value;
}
