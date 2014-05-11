#include <stdio.h>
#include <ctype.h>
#include "structure.hpp"
#include "parser.hpp"
#include "lexer.hpp"
#include "init.hpp"
#include "DAGIR.hpp"
using namespace std;

stack<int> result;
stack <Pii> _stack;			//fir = 状态, sec = dag节点值编码
extern int nDag ;

void parse_init()
{
	while (!_stack.empty()) _stack.pop();
	nDag = 1;
}
void parser()
{
	_stack.push(Pii(0, 0));
	Token tok = nextToken();
	while (true) {
		int  I = _stack.top().first;
		TokenType a = tok.type;
		if (action[I][a] == ACCEPT) {
			break;
		} else if (action[I][a] == ERROR) {
			fprintf(stderr, "该句子不是合法句子: %c\n", a);
			exit(0);
		} else if (action[I][a] > 0) {
			shift(action[I][a], tok);
			tok = nextToken();
		} else {
			reduce(-action[I][a]);
		}
	}
	printf("接受\n");
	while (!result.empty()) printf(">>> %d\n", result.top()), result.pop() ;
}

void shift(int I, Token tok)
{
	printf("移入\n");
	_stack.push(Pii(I, lookupDAG(tok.type, tok.ctx, 0)));
}

void reduce(int pid)			//按规则pid归约
{
	Product & p = pro[pid];

	switch (pid) {
		case 0 :          break;
		case 1 : sdt1(p); break;
		case 2 : sdt2(p); break;
		case 3 : sdt3(p); break;
		case 4 : sdt4(p); break;
		case 5 : sdt5(p); break;
		case 6 : sdt6(p); break;
		case 7 : sdt7(p); break;
		case 8 : sdt8(p); break;
		case 9 : sdt9(p); break;
		case 10: sdt10(p);break;
		default : break;
	}
	
	printf("根据规则%c -> %s 归约\n", p.left, p.right.c_str());
}

void sdt1(Product & p)
{
	int r = _stack.top().second;
	_stack.pop();
	Type op = dagTable[_stack.top().second].op;
	_stack.pop();
	int l = _stack.top().second;
	_stack.pop();

	int I = _stack.top().first;
	
	_stack.push( Pii(GOTO[I][p.left], lookupDAG(op, l, r)) );
}
void sdt2(Product & p)
{
	int l = _stack.top().second;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], l) );
}

void sdt3(Product & p)
{
	int r = _stack.top().second;
	_stack.pop();
	Type op = dagTable[_stack.top().second].op;
	_stack.pop();
	int l = _stack.top().second;
	_stack.pop();
	
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], lookupDAG(op, l, r)) );
}
void sdt4(Product & p)
{
	int l = _stack.top().second;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], l) );
}
void sdt5(Product & p)
{
	_stack.pop();
	int l = _stack.top().second;
	_stack.pop();
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], l) );
}
void sdt6(Product & p)
{
	int l = _stack.top().second;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], l) );
}
void sdt7(Product & p)
{
	int l = _stack.top().second;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], l) );
}
void sdt8(Product & p)
{
	_stack.pop();
	int r = _stack.top().second;
	_stack.pop();
	Type op = dagTable[_stack.top().second].op;
	_stack.pop();
	int l = _stack.top().second;
	_stack.pop();

	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], lookupDAG(op, l, r)) );
}
void sdt9(Product & p)
{
	int r = _stack.top().second;
	_stack.pop();
	Type op = dagTable[_stack.top().second].op;
	_stack.pop();
	int l = _stack.top().second;
	_stack.pop();

	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], lookupDAG(op, l, r)) );

	result.push(dagTable[l].getVal());
}
void sdt10(Product & p)
{
	int l = _stack.top().second;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pii(GOTO[I][p.left], l) );
}
