#ifndef			__EVAL_H__
#define			__EVAL_H__
#include "structure.h"

NumNode * eval(Node *) ;

NumNode * Eeval(Node *);
NumNode * E1eval(Node *);
NumNode * Teval(Node *);
NumNode * T1eval(Node *);
NumNode * Feval(Node *);
NumNode * TerminalEval(Node *);

#endif
