#ifndef 	__PARSER_H__
#define		__PARSER_H__
#include "structure.h"
#include "lexer.h"

Node * parser() ;

Node * E_match() ;
Node * E1_match() ;
Node * T_match() ;
Node * T1_match() ;
Node * F_match() ;
Node * match(TokenType type) ;

#endif
