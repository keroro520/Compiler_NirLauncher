#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "error.h"
#include "lexer.h"
static char yytext[1000];
static char c;
static int len = 0;				//yytext len
static char * symTable[4096];
static Stat * statTable[4096];

void buildDFA()
{
	FILE * f = fopen("dfa.txt", "r");
	int n, m;
	fscanf(f, "%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int x; 
		StatType type;
		fscanf(f, "%d %d", &x, &type);
		statTable[x] = malloc(sizeof (Stat)); 
		statTable[x]->type = type;
		statTable[x]->isTerminal = true;
	}

	while(m--) {
		int a, b;
		char c;
		fscanf(f, "%d %d %c", &a, &b, &c);
		if (!statTable[a]) statTable[a] = malloc(sizeof (Stat));
		if (!statTable[b]) statTable[b] = malloc(sizeof (Stat));
		statTable[a]->next[c] = statTable[b];
	}
	fclose(f);

	for (const char * ch = alphas; *ch; ch++) {
		statTable[0]->next[*ch] = statTable[3];
		statTable[3]->next[*ch] = statTable[3];
	}
	for (const char * ch = alnums; *ch; ch++) {
		statTable[3]->next[*ch] = statTable[3];
	}
	for (const char * ch = nums; *ch; ch++) {
		statTable[0]->next[*ch] = statTable[4];
		statTable[4]->next[*ch] = statTable[4];
	}
}

int lookup(char * s)
{
	int i;
	for (i = 0; symTable[i]; i++) {
		if (strcmp(symTable[i], s) == 0) return i;
	}
	symTable[i] = (char *) malloc((sizeof(char)) * len);
	strcpy(symTable[i], s);
	return i;
}

TokenType lex(const Stat * p)
{
	if (c == EOF || !p->next[c]) {
		if(p->isTerminal) {
			yytext[len++] = '\0';
			return p->type;
		} else {
			yytext[len++] = c;
			yytext[len++] = '\0';
			lexError("cannot reganize", yytext);
		}
	}
	char oldc = c;
	yytext[len++] = c;
	c = getchar();

	return lex(p->next[oldc]);
}

TokenType nextToken()
{
	while(isspace(c)) c = getchar();
	if (c == EOF) return LEXEOF;
	len = 0;

	StatType t = lex(statTable[0]);
	if  (strcmp("define", yytext) == 0) return DEFINE;
	else if (strcmp("if", yytext) == 0) return IF;
	else return t;
}

int main()
{
	buildDFA();
	c = getchar();
	while(nextToken() != LEXEOF) printf("%s\n", yytext);
	return 0;
}
