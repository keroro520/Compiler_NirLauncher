#include <string.h>
#define		NTOKENS			10000

enum Type {
	ROOT = 0,
	LPARENT = 1,
	RPARENT = 2,
	ID = 3,
	NUMBER = 4,
	ADD = 5,
	SUB = 6,
	MUL = 7,
	DIV = 8,
	ASSIGN = 9,
	DEFINE = 100,
	IF     = 101,
	NONTERMINAL = 90,
	LEXEOF = -1
};

typedef		Type 	NodeType;
class Node {
	#define		NNODENEXT		256
	public :
	NodeType type;
	bool isTerminal;
	Node * next[NNODENEXT];
	Node () {
		isTerminal = false;
		memset(next, 0, sizeof next);
	}
	Node (NodeType type, bool isTerminal) : type(type), isTerminal(isTerminal) { }
} ;

typedef		Type	TokenType;
class Token {
	public :
	TokenType type;
	int sym;
	Token () { }
	Token (TokenType type, int sym) : type(type), sym(sym) { }
} ;

Token * tokens[NTOKENS];
int token_index = 0;
