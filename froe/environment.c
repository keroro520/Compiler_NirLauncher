#include <stdlib.h>
#include "environment.h"
#include "structure.h"
#include "eval.h"

#define		error(s,s2)		fprintf(stderr, "%s : \"%s\"\n", (s), (s2))

extern int evalError;
extern Env top;

Node * lookup(Env * env, SymNode * sym)
{
	Refer i = sym->name;
	do {
		if (env->sym[i] != NULL) return env->sym[i];
		env = env->father;
	} while (env) ;
	error("*** ERROR:lookup:\nUnbound variable", refer2Str(sym->name));
	evalError = 1;
	return NULL;
}
void updateEnv(Env * env, SymNode * sym, Node * value) 
{
	env->sym[sym->name] = value;
}
