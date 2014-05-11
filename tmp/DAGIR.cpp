#include <stdio.h>
#include "DAGIR.hpp"
#include "environment.hpp"
using namespace std;

DAG dagTable[1948];
int nDag ;

int _calc(Type op, int l, int r) ;
int lookupDAG(Type op, int l, int r)
{
	for (int i = 1; i < nDag; i++) {
		if (dagTable[i].op == op && dagTable[i].l == l && dagTable[i].r == r) {
			return i;
		}
	}
	dagTable[nDag].op = op;
	dagTable[nDag].l  = l ;
	dagTable[nDag].r  = r ;
	dagTable[nDag].val=_calc(op, l, r);

	return nDag++;
}
int _calc(Type op, int l, int r) 
{
	if (op == NUM) return l;
	if (r == 0) return 0;				//因为符号shift的时候把'+', '('等符号扔进来了=_= 直接忽略
																//这样一来剩下的都是表达式或者ID/NUM了~~
	switch (op) {
		case ADD : 
			return dagTable[l].getVal() + dagTable[r].getVal();
		case MUL : 
			return dagTable[l].getVal() * dagTable[r].getVal();
		case ASSIGN : 
			updateEnv(dagTable[l].l, dagTable[r].getVal()); 
			return lookup(dagTable[l].l);
		case SEMICOLON :
			return dagTable[l].getVal();
		default : printf("!!! what happen in FILE \"DAGIR.cpp\" _calc() %d\n", op); return 0; 
	}
}
