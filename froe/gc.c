#include <stdio.h>
#include "gc.h"

void _decrease(__ADDR addr) ;
void decrease_(__ADDR addr) ;
void _increase(__ADDR addr) ;

void _gc(Node * l, Node * r)
{
	__ADDR addr;
	if (l != NULL) {
		addr = (__ADDR) l;
		_decrease(addr);
	}
	if (r != NULL) {
		addr = (__ADDR) r;
		_increase(addr);
	}
	l = r;
}

void freeNode(Node * a)
{
}

int hash(__ADDR addr)
{
	return (int) (addr % 1984) ;		//FIXME
}
void _decrease(__ADDR addr)
{
	int i = hash(addr);
	if (--gcTable[i] == 0) freeNode((Node *) addr);
}
void _increase(__ADDR addr)
{
	int i = hash(addr);
	gcTable[i]++;	
}
void decrease_(__ADDR addr)
{
	int i = hash(addr);
	if (gcTable[i]-- == 0) freeNode((Node *) addr);
}
