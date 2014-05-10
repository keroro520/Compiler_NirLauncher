#include <stdio.h>
#include <ctype.h>
#include "lexer.h"

#define		lexError(s, c)		fprintf(stderr, "%s: %c\n", (s), (c))

char c = ' ';

Token nextToken()
{
	Token ret = {.type = EOF} ;
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
		ret.ctx  = str2Refer(yytext);
	} else if (isdigit(c)) {
		while (isdigit(c)) {
			yytext[yylen++] = c;
			c = getchar();
		}
		yytext[yylen++] = '\0';
		ret.type = NUM;
		ret.ctx  = str2Refer(yytext);
	} else {
		switch (c) {
			case '+' : c = getchar(); ret.type = ADD; 	  ret.ctx = str2Refer("+"); break;
			case '-' : c = getchar(); ret.type = SUB; 	  ret.ctx = str2Refer("-"); break;
			case '*' : c = getchar(); ret.type = MUL; 	  ret.ctx = str2Refer("*"); break;
			case '/' : c = getchar(); ret.type = DIV; 	  ret.ctx = str2Refer("/"); break;
			case '(' : c = getchar(); ret.type = LPARENT; ret.ctx = str2Refer("("); break;
			case ')' : c = getchar(); ret.type = RPARENT; ret.ctx = str2Refer(")"); break;
			default  : lexError("Unreganize character", c); exit(0); 
		}
	}
	return ret;
}
