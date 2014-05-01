#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"
#include "structure.h"

#define lexError(s, c) { fprintf(stderr, "Lex error : %s \'%c\'\n", (s), (c)); }

char c = ' ';
Token TOKENEOF = {.type = LEXEOF};

bool isspec(char ch)
{
	const char * a = "!$%&*+-./:<=>?@^_~";
	while(*a != '\0') {
		if (*a++ == ch) {
			return true;
		}
	}
	return false;
}

Token nextToken()
{
	while( isspace(c) ) c = getchar();
	
	yylen = 0;
	Token ret;

	if (c == EOF) {
		ret.type = LEXEOF;
		return ret;
	}

	if (isdigit(c)) {
		while (isdigit(c)) {
			yytext[yylen++] = c;
			c = getchar();
		}
		yytext[yylen++] = '\0';
		ret.type = NUM;
		ret.name = str2Refer(yytext);
	} else if (isalpha(c)) {
		while (isalnum(c) || isspec(c)) {
			yytext[yylen++] = c;
			c = getchar();
		}
		yytext[yylen++] = '\0';
		ret.type = ID;
		ret.name = str2Refer(yytext);
	} else {
		switch (c) {
			case '(' : ret.type = LPARENT; c = getchar(); break;
			case ')' : ret.type = RPARENT; c = getchar(); break;
			default  : 
				lexError("Unreganize character", c);
				exit(0);
		}
	}
	return ret;
}
