#ifndef		__STRUCTURE_H__
#define		__STRUCTURE_H__

#define		NEW(t)		malloc(sizeof (t))
#define		toSym(a)	((SymNode *)(a))
#define		toStr(a)	((StrNode *)(a))
#define		toBool(a)	((BoolNode*)(a))
#define		toNum(a)	((NumNode *)(a))
#define		toList(a)	((ListNode*)(a))
#define		toPair(a)	((PairNode*)(a))
#define		toCall(a)	((CallNode*)(a))
#define		toLambda(a)	((LambdaNode *)(a))
#define		toDef(a)	((DefNode *)(a))
#define		toProc(a)	((ProcNode*)(a))
#define		toBui(a)	((BuiltinNode *)(a))
#define		toAtom(a)	((AtomNode*)(a))

#define		cdar		cdr->car
#define		cddar		cdr->cdr->car

typedef		int		Refer;
typedef struct Env Env;

typedef enum NodeType {
	SYMBOL = 11,
	NUMBER,
	STR,
	BOOL,
	DEFINE,
	LAMBDA,
	CALL,
	PROC,
	BUILTIN,
	LIST,
	PAIR,
	ATOM
} NodeType;

typedef struct Node {
	NodeType type;
} Node ;

typedef struct SymNode {
	NodeType type;
	Refer name;
} SymNode ;

typedef struct NumNode {
	NodeType type;
	int value;
} NumNode ;

typedef struct StrNode {
	NodeType type;
	Refer name;
} StrNode ;

typedef struct BoolNode {
	NodeType type;
	int value;
} BoolNode ;

typedef struct PairNode {
	NodeType type;
	Node * car;
	Node * cdr;
} PairNode ;

typedef struct ListNode {
	NodeType type;
	Node * car;
	struct ListNode * cdr;
} ListNode ;

typedef struct LambdaNode {
	NodeType type;
	ListNode * formal;
	Node * body;
} LambdaNode ;

typedef struct DefNode {
	NodeType type;
	SymNode  * sym;
	ListNode * formal;
	Node * body;
} DefNode ;

typedef struct CallNode {
	NodeType type;
	Node * sym;
	ListNode * args;
} CallNode ;

typedef struct ProcNode {
	NodeType type;
	ListNode * formal;
	Node * body;
	Env  * env;
} ProcNode ;

typedef struct BuiltinNode {
	NodeType type;
	Node * (* addr)(ListNode *, Env *);
} BuiltinNode ;

typedef struct AtomNode {
	NodeType type;
	Refer	 name;
} AtomNode ;

SymNode * newSymNode (Refer name) ;
StrNode * newStrNode (Refer name) ;
BoolNode* newBoolNode(int value)  ;
NumNode * newNumNode (int  value) ;
PairNode* newPairNode(Node * car, Node * cdr) ;
ListNode* newListNode(Node * car, Node * cdr) ; 
LambdaNode* newLambdaNode(ListNode * formal, Node * body) ; 
DefNode* newDefNode(SymNode * sym, ListNode * formal, Node * body) ;
CallNode* newCallNode(Node * sym, ListNode * args) ;
ProcNode* newProcNode(ListNode * formal, Node * body, Env * env) ;
BuiltinNode * newBuiltinNode (Node * (*)(ListNode *, Env *)) ;
AtomNode* newAtomNode(Refer name) ;

Refer  str2Refer(char *) ;
char * refer2Str(Refer ) ;
int refer2Num(Refer i) ;
void printNode(Node * a) ;

ListNode * append(ListNode * a, Node * b) ;
PairNode * cons(Node * a, Node * b) ;
Node * car(Node * a) ;
Node * cdr(Node * a) ;
int len(Node * a) ;


char * strTable[1984];
ListNode nil;
#endif
