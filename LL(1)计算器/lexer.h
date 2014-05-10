#ifndef			__LEXER_H__
#define			__LEXER_H__
#include "structure.h"

typedef enum TokenType {
	ID = 11,
	NUM,
	LPARENT,
	RPARENT,
	ADD,
	SUB,
	MUL,
	DIV,
	LEXEOF = EOF
} TokenType ;

typedef struct Token {
	TokenType type;
	Refer ctx;
} Token ;

Token nextToken() ;

char yytext[1984];
int  yylen;

#endif
