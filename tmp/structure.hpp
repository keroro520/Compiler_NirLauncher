#ifndef		__STRUCTURE_H__
#define		__STRUCTURE_H__
#include <algorithm>
#include "init.hpp"
#include "environment.hpp"

#define		for_each(i, c)		for (auto i = (c).begin(); i != (c).end(); i++) 

template<class T, class T2> bool IN(T C, T2 x)
{
	return std :: find(C.begin(),C.end(),x) != C.end();
}

enum Type {
	NUM		= '1',
	ID 		= 'i',
	LPARENT = '(',
	RPARENT = ')',
	ADD 	= '+',
	MUL 	= '*',
	ASSIGN	= '=',
	LEXEOF 	= '$',

	E 		= 'E',
	F 		= 'F',
	S 		= 'S',
	T 		= 'T',
} ;
typedef		enum Type		Type ;
typedef     enum Type   	TokenType ;

typedef struct Token {
    TokenType type;
	Refer ctx;
} Token ;

class Node {
	public :
	Type type;
	int val;
	Node () { }
	Node (Type type, int val) : type(type), val(val) { }
	Node (Token tok) : type(tok.type) {
		val = 1;					//FIXME
	}
} ;


Node * newNode(Type type, int val) ;
Node * newNode(Token tok) ;
void   freeNode(Node * )   ;

#endif
