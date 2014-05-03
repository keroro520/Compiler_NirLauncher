#ifndef			__GC_H__
#define			__GC_H__
#include "structure.h"

#define		gc(l,r)		{ _gc((Node *)(l), (Node *)(r)); }

typedef			long long   			__ADDR;

void _gc(Node * l, Node * r) ;
void decrease(__ADDR addr) ;
void increase(__ADDR addr) ;

void freeNode(Node *) ;

int gcTable[1984];

#endif
