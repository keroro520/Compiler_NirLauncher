#ifndef			__PARSER_HPP__
#define			__PARSER_HPP__
#include <stack>
#include "init.hpp"
#include "structure.hpp"

typedef		std :: pair<int,int>		Pii;

void parser() ;
void shift(int I, Token tok) ;
void reduce(int pid) ;
void sdt1(Product & p) ;
void sdt2(Product & p) ;
void sdt3(Product & p) ;
void sdt4(Product & p) ;
void sdt5(Product & p) ;
void sdt6(Product & p) ;
void sdt7(Product & p) ;
void sdt8(Product & p) ;
void sdt9(Product & p) ;
void sdt10(Product & p) ;


extern std :: stack<Pii>  _stack;
extern std :: stack<int>  result;

#endif
