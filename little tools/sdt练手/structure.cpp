#include "structure.hpp"
#include "lexer.hpp"
#include "environment.hpp"

Node * newNode(Type type, int val)
{
	Node * t = new Node(type, val);
	return t;
}
Node * newNode(Token tok) 
{
	Node * t ;
	if (tok.type == NUM) t = new Node(NUM, stoi(ref2str(tok.ctx)));
	else if (tok.type == ID) t = new Node(ID, tok.ctx);
	else t = new Node(tok);
	return t;
}

void freeNode(Node * a)
{
	free(a);
}
