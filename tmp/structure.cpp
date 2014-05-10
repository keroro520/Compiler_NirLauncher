#include "structure.hpp"
#include "lexer.hpp"

Node * newNode(Type type, int val)
{
	Node * t = new Node(type, val);
	return t;
}
Node * newNode(Token tok) 
{
	Node * t = new Node(tok);
	return t;
}

void freeNode(Node * a)
{
	free(a);
}
