#ifndef			__DAGIR_HPP__
#define			__DAGIR_HPP__
#include "structure.hpp"
#include "environment.hpp"
/*
	op = ID : l = id.ctx, r = 0
	op = NUM: l = id.ctx, r = 0
*/
class DAG {
	public :
	Type op;
	int  l;
	int  r;
	int  val;
	DAG () 											 { }
	DAG (Type op, int l) 		: op(op), l(l) 		 { }
	DAG (Type op, int l, int r) : op(op), l(l), r(r) { }
	int getVal() {
		if (op == ID) return lookup(l);
		return val;
	}
} ;


int  lookupDAG(Type op, int l, int r) ;
void calcDAG() ;

extern DAG dagTable[1948];			/* dagTable[0] 无意义 */
extern int nDag ;
#endif
