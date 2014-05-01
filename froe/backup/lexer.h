#include <string.h>
#include <stdbool.h>

typedef enum Type {
	ROOT = 0,
	LPARENT = 1,
	RPARENT = 2,
	ID = 3,
	NUMBER = 4,

	IF,
	DEFINE,

	LEXEOF = -1
} Type;

typedef		Type 	StatType;
typedef struct Stat {
	#define		NNODENEXT		256
	StatType type;
	bool isTerminal;
	struct Stat * next[NNODENEXT];
} Stat;

typedef 	struct Node 	Node;

typedef		Type	TokenType;
typedef struct Token {
	TokenType type;
	Node * lit;
} Token;

const char * extAlphas = "!$%&*+-./:<=>?@~^_";
const char * alphas = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
const char * nums   = "1234567890";
const char * alnums = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890!$%&*+-./:<=>?@~^_";
