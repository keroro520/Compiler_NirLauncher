#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"
#include "lexer.h"
#include "parser.h"

#define		error(s)		fprintf(stderr, "%s\n", (s)) 
static int  depth = 0;
static bool endOfList = false;

Node * parser() ;
ListNode * parseList() ;

Node * parsePair()
{
	Node * a = parser();

	if (a->type == SYMBOL && 0 == strcmp(refer2Str(toSym(a)->name), "lambda")) {	// (lambda (args*) (body)) 
		if (nextToken().type != LPARENT) {
			error("Illegal identifier type");
			exit(0);
		}
		depth++;
		a = (Node *) newLambdaNode(parseList(), parser());
		if (nextToken().type != RPARENT) {
			error("Illegal identifier type");
			exit(0);
		}
		depth--;
		return a;
	} else if (a->type == SYMBOL && 0 == strcmp(refer2Str(toSym(a)->name), "define")) {	
		a = parser();
		if (a->type == SYMBOL) {													//(define x (y)|y) 定义变量
			a = (Node *) newDefNode(toSym(a), NULL, parser());
		} else if (a->type == PAIR) {												//(define (f ..) (body)|body)
			if (toPair(a)->car->type != SYMBOL) {
				error("Illegal identifier type");
				exit(0);
			}
			a = (Node *) newDefNode(toSym(toPair(a)->car), toList(toPair(a)->cdr), parser());
		} else {
			error("Illegal identifier type");
			exit(0);
		}
		if (nextToken().type != RPARENT) {
			error("Illegal identifier type");
			exit(0);
		}
		depth--;
		return a;
	} else {
		ListNode * b = parseList();
		return (Node *) newPairNode(a, (Node *)b);
	}
}

ListNode * parseList()
{
	ListNode * a = NEW(ListNode);
	ListNode * t = a;
	a->type = LIST;
	a->car  = parser();
	while (endOfList == false) {
		Node * b = parser();
		if (endOfList) break;
		a = append(a, b)->cdr;
	}
	endOfList = false;
	return t;
}

Node * parser()
{
	Token tok = nextToken();
	switch (tok.type) {
		case LPARENT : 
			depth ++; 
			return parsePair() ;
		case RPARENT : 
			endOfList = true;
			depth --;
			if (depth < 0) {
				error("Unmatch parenrts");
				exit(0);
			}
			return NULL;
		case NUM :
			return (Node *) newNumNode(refer2Num(tok.name));
		case ID :
			return (Node *) newSymNode(tok.name);
		case LEXEOF :
			if (depth != 0) {
				error("Unmatched parents"); 
				exit(0);
			}
			endOfList = true;
			return NULL;
		default : 
			error("Unknown token");
			exit(0);
	}
}
