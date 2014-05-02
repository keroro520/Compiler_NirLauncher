#ifndef 	__LERXER_H__
#define		__LERXER_H__
#include <stdio.h>
#include "structure.h"
enum TokenType {
	LPARENT = 10,
	RPARENT = 11,
	ID		= 31,
	NUM		= 32,
	STRING	= 33,
	BOOLTRUE	= 34,
	BOOLFALSE	= 35,
	_ATOM	= 36,

	LEXEOF	= EOF
} ;

typedef struct Token {
	enum TokenType type;
	Refer     name;
} Token;

Token nextToken() ;

extern Token TOKENEOF;
extern char c ;
char yytext[1024];
int  yylen;

#endif
