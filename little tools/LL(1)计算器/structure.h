#ifndef		__STRUCTURE_H__
#define		__STRUCTURE_H__
#include 	<stdlib.h>
#define			NEW(t)		(t *)malloc(sizeof (t))
#define			toTer(a)	((TerminalNode *)(a))
#define			toNum(a)	((NumNode *)(a))

typedef		int		Refer ;

typedef enum NodeType {
	E = 1,
	E1,
	T,
	T1,
	F,
	TERMINAL,
} NodeType ;

typedef struct Node {
	NodeType type;
	struct Node * child;
	struct Node * brother;
} Node ;

typedef struct TerminalNode {
	NodeType type ;
	Refer ctx;
} TerminalNode ;

typedef struct NumNode {
	NodeType type ;
	int val;
} NumNode ;

Node * newNode(NodeType type) ;
NumNode * newNumNode(int val) ;
TerminalNode * newTerminalNode(Refer ctx) ;
void printNode(Node * ) ;
Refer str2Refer(char * ) ;
char * refer2Str(Refer i) ;
int stoi(char * );


char * strTable[1984];
#endif
