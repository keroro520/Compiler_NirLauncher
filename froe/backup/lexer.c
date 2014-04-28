#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "error.hpp"
#include "lexer.hpp"
#define		debug		printf("!\n")
static char yytext[1000];
static char c;
static int len = 0;				//yytext len
static char * symTable[4096];
static Node * statTable[4096];

void buildDFA()
{
	FILE * f = fopen("dfa.txt", "r");
	int n, m;
	fscanf(f, "%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int x; 
		NodeType type;
		fscanf(f, "%d %d", &x, &type);
		statTable[x] = new Node(type, true);
	}

	while(m--) {
		int a, b;
		char c;
		fscanf(f, "%d %d %c", &a, &b, &c);
		if (!statTable[a]) statTable[a] = new Node();
		if (!statTable[b]) statTable[b] = new Node();
		statTable[a]->next[c] = statTable[b];
	}
	fclose(f);

	const char * alphas = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_\0";
	const char * nums   = "1234567890\0";
	for (const char * ch = alphas; *ch; ch++) {
		statTable[0]->next[*ch] = statTable[3];
		statTable[3]->next[*ch] = statTable[3];
	}
	for (const char * ch = nums; *ch; ch++) {
		statTable[3]->next[*ch] = statTable[3];
		statTable[0]->next[*ch] = statTable[4];
		statTable[4]->next[*ch] = statTable[4];
	}
}

int lookup(char * s)
{
	int i;
	for (i = 0; symTable[i]; i++) {
		if (strcmp(symTable[i], s) == 0 ) return i;
	}
	symTable[i] = (char *) malloc((sizeof(char)) * len);
	strcpy(symTable[i], s);
	return i;
}

void insertToken(TokenType type)
{
	if (strcmp("define", yytext) == 0) tokens[token_index++] = new Token(DEFINE, -1);
	else if (strcmp("if", yytext) == 0) tokens[token_index++] = new Token(IF, -1);
	else tokens[token_index++] = new Token(type, lookup(yytext));
	len = 0;
}

TokenType lex(const Node * p)
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

int main()
{
	buildDFA();
	c = getchar();
	while (true) {
		while(isspace(c)) c = getchar();
		if (c == EOF) break;
		insertToken( lex(statTable[0]) );
	}
	for(int i = 0; i < token_index; i++) printf("%s %d\n", symTable[tokens[i]->sym], tokens[i]->type);
	return 0;
}
