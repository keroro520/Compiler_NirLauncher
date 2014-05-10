#include <stdio.h>
#include <ctype.h>
#include <stack>
#include "structure.hpp"
#include "parser.hpp"
using namespace std;

stack<int> S;

char nextToken(FILE * f)
{
	char ch;
	while (isspace(ch = getc(f))) ;
	return ch == EOF ? eof : ch;
}

void shift(int I)
{
	printf("移入\n");
	S.push(I);
}

void reduce(int pid, char a)			//按规则pid归约
{
	Product & p = pro[pid];
	int l = p.right.length();
	while (l--) S.pop();
	
	int I = S.top();
	S.push(GOTO[I][p.left]);
	printf("根据规则%c -> %s 归约\n", p.left, p.right.c_str());
}

void parser()
{
	S.push(0);
	char a = nextToken(stdin);
	while (true) {
		int  I = S.top();
		if (action[I][a] == ACCEPT) {
			break;
		} else if (action[I][a] == ERROR) {
			fprintf(stderr, "该句子不是合法句子: %c\n", a);
			exit(0);
		} else if (action[I][a] > 0) {
			shift(action[I][a]);
			a = nextToken(stdin);
		} else {
			reduce(-action[I][a], a);
		}
	}
	printf("接受\n");
}
