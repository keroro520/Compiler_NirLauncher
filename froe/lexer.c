#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "lexer.h"
#include "structure.h"

#define lexError(s, c) { fprintf(stderr, "Lex error : %s \'%c\'\n", (s), (c)); exit(0);}

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
	} else if (c == '\"') {
		while ((c = getchar()) != '\"') {
			if (c == '\\') yytext[yylen++] = getchar();
			else 		   yytext[yylen++] = c;
		}
		yytext[yylen++] = '\0';
		ret.type = STRING;
		ret.name = str2Refer(yytext);
		c = getchar();
	} else if (c == '\'') {
		c = getchar();
		if ((ret = nextToken()).type == LPARENT) {
			yytext[yylen++] = '(';
			yytext[yylen++] = c;
			int depth = c == ')' ? 0 : 1;
			while(depth) {
				yytext[yylen++] = c = getchar();
				if (c == ')') depth--;
			}
			yytext[yylen++] = '\0';
			c = getchar();
		}
		ret.type = _ATOM;
		ret.name = str2Refer(yytext);
	} else if (c == '#') {
		c = getchar();
		ret = nextToken();
		if (0 != strcmp(yytext, "t") && 0 != strcmp(yytext, "f")) {
			lexError("Unreganize character", yytext[0]);
		}
		ret.type = yytext[0] == 't' ? BOOLTRUE : BOOLFALSE;
	} else if (isalpha(c) || isspec(c)) {
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
			case ';' : while(getchar() != '\n') ; c = getchar(); return nextToken(); 
			default  : 
				lexError("Unreganize character", c);
		}
	}
	return ret;
}
