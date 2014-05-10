#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "lexer.hpp"

#define		lexError(s, c)		fprintf(stderr, "%s: %c\n", (s), (c))

static char c = ' ';
char yytext[1984];
int  yylen ;

Token nextToken()
{
	Token ret = {.type = LEXEOF} ;
	while (isspace(c)) c = getchar();
	if (c == EOF) return ret;
	
	yylen = 0;

	if (isalpha(c)) {
		while (isalnum(c)) {
			yytext[yylen++] = c;
			c = getchar();
		}
		yytext[yylen++] = '\0';
		ret.type = ID;
		ret.ctx  = str2ref(yytext);
	} else if (isdigit(c)) {
		while (isdigit(c)) {
			yytext[yylen++] = c;
			c = getchar();
		}
		yytext[yylen++] = '\0';
		ret.type = NUM;
		ret.ctx  = str2ref(yytext);
	} else {
		switch (c) {
			case '+' : c = getchar(); ret.type = ADD; 	  ret.ctx = str2ref("+"); break;
			case '*' : c = getchar(); ret.type = MUL; 	  ret.ctx = str2ref("*"); break;
			case '(' : c = getchar(); ret.type = LPARENT; ret.ctx = str2ref("("); break;
			case ')' : c = getchar(); ret.type = RPARENT; ret.ctx = str2ref(")"); break;
			case '=' : c = getchar(); ret.type = ASSIGN ; ret.ctx = str2ref("="); break;
			default  : lexError("Unreganize character", c); exit(0); 
		}
	}
	return ret;
}
