#include <stdio.h>
#include "parser.h"
#include "lexer.h"

#define		error(s1,s2)			fprintf(stderr, "%s: %s\n", (s1), (s2));

Token tok;

Node * parser()
{
	tok = nextToken();
	return E_match();
}
Node * match(TokenType type)
{
	if (tok.type != type) {
		error("Unexpected token", yytext);	
		exit(0);
	}
	
	TerminalNode * t = newTerminalNode(tok.ctx);
	
	tok = nextToken();
	
	return (Node *) t;
}
Node * E_match() 
{
	Node * t = newNode(E), * a = NULL, * b;
	switch (tok.type) {
		case ID : case NUM : case LPARENT :
			a = T_match();  t->child   = a; b = a;
			a = E1_match(); b->brother = a;
			break;
		default : error("Unexpected token", yytext); exit(0);
	}
	return t;
}
Node * E1_match()
{
	Node * t = newNode(E1), * a = NULL, * b;
	switch (tok.type) {
		case ADD : case SUB :
			a = match(tok.type); t->child   = a; b = a;
			a = T_match();  b->brother = a; b = a;
			a = E1_match(); b->brother = a;
			break;
		case RPARENT : case EOF :
			break;
		default : error("Unexpected token", yytext);	 exit(0);
	}
	return t;
}
Node * T_match() 
{
	Node * t = newNode(T), * a = NULL, * b;
	switch (tok.type) {
		case ID : case NUM: case LPARENT :
			a = F_match();  t->child   = a; b = a;
			a = T1_match(); b->brother = a; 
			break;
		default : error("Unexpected token", yytext);	 exit(0);
	}
	return t;
}
Node * T1_match() 
{
	Node * t = newNode(T1), * a = NULL, * b;
	switch (tok.type) {
		case MUL : case DIV :
			a = match(tok.type); t->child = a; b = a;
			a = F_match();  b->brother = a;    b = a;
			a = T1_match(); b->brother = a; 
			break;
		case ADD : case SUB: case RPARENT : case EOF :
			break;
		default : error("Unexpected token", yytext);	 exit(0);
	}
	return t;
}
Node * F_match() 
{
	Node * t = newNode(F), * a = NULL, * b;
	switch (tok.type) {
		case ID : case NUM:
			a = match(tok.type); t->child = a;
			break;
		case LPARENT :
			a = match(LPARENT);	t->child   = a; b = a;
			a = E_match();		b->brother = a; b = a;
			a = match(RPARENT); b->brother = a; 
			break;
		default : error("Unexpected token", yytext);	 exit(0);
	}
	return t;
}
