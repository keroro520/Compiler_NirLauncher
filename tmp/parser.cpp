#include <stdio.h>
#include <ctype.h>
#include "structure.hpp"
#include "parser.hpp"
#include "lexer.hpp"
#include "init.hpp"
using namespace std;

stack<Pin> _stack;


void parser()
{
	while (!_stack.empty()) _stack.pop();
	_stack.push(Pin(0, newNode(E, 0)));
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
	printf("接受 %d\n", _stack.top().second->val);
}

void shift(int I, Token tok)
{
	printf("移入\n");
	Node * t = newNode(tok);
	_stack.push(Pin(I, t));
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
		default : break;
	}
	
	printf("根据规则%c -> %s 归约\n", p.left, p.right.c_str());
}

void sdt1(Product & p)
{
	Node * a = _stack.top().second;
	_stack.pop();
	_stack.pop();
	Node * b = _stack.top().second;
	_stack.pop();
	Node * t = newNode(E, a->val + b->val);
	freeNode(a);
	freeNode(b);
	
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], t) );
}
void sdt2(Product & p)
{
	Node * a = _stack.top().second;
	a->type = E;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], a) );
}

void sdt3(Product & p)
{
	Node * a = _stack.top().second;
	_stack.pop();
	_stack.pop();
	Node * b = _stack.top().second;
	_stack.pop();
	Node * t = newNode(T, a->val * b->val);
	freeNode(a);
	freeNode(b);
	
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], t) );
}
void sdt4(Product & p)
{
	Node * a = _stack.top().second;
	a->type = T;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], a) );
}
void sdt5(Product & p)
{
	_stack.pop();
	Node * a = _stack.top().second;
	a->type  = F;
	_stack.pop();
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], a) );
}
void sdt6(Product & p)
{
	Node * a = _stack.top().second;
	a->type = F;
	a->val  = lookup(a->val);
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], a) );
}
void sdt7(Product & p)
{
	Node * a = _stack.top().second;
	a->type = F;
	_stack.pop();
	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], a) );
}
void sdt8(Product & p)
{
	Node * expr = _stack.top().second;
	_stack.pop();
	_stack.pop();
	Node * a    = _stack.top().second;
	_stack.pop();

	updateEnv(a, expr->val);

	a->type = E;
	a->val  = expr->val;

	int I = _stack.top().first;
	_stack.push( Pin(GOTO[I][p.left], a) );
}
