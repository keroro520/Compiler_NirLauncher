#include <stdio.h>
#include "gc.h"

void decrease(__ADDR addr) ;
void increase(__ADDR addr) ;

void _gc(Node * l, Node * r)
{
	__ADDR addr;
	if (l != NULL) {
		addr = (__ADDR) l;
		decrease(addr);
	}
	if (r != NULL) {
		addr = (__ADDR) r;
		increase(addr);
	}
}

void freeNode(Node * a)
{
}

int hash(__ADDR addr)
{
	return (int) (addr % 1984) ;		//FIXME
}
void decrease(__ADDR addr)
{
	int i = hash(addr);
	if (--gcTable[i] == 0) freeNode((Node *) addr);
}
void increase(__ADDR addr)
{
	int i = hash(addr);
	gcTable[i]++;	
}
