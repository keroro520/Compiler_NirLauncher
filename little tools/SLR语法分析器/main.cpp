#include <stdio.h>
#include <iostream>
#include "structure.hpp"
#include "init.hpp"
#include "parser.hpp"
using namespace std;

void output()
{
	for (auto it = pro.begin(); it != pro.end(); it ++) {
		cout << it->left << "\t" << it->right << "\t" << endl;
	}
	cout << endl;
	cout << endl;
	for (auto it = nonTerminal.begin(); it != nonTerminal.end(); it++) {
		cout << "fir(" << *it << ") = { " ;
		for (auto i = first[*it].begin(); i != first[*it].end() ; i++) cout << *i << " , " ;
		cout << "}" << "\t\tfol(" << *it << ") = { " ;
		for (auto i = follow[*it].begin(); i != follow[*it].end() ; i++) cout << *i << " , " ;
		cout << "}"<<endl;
	}
	for (auto it = LR0Stats.begin(); it != LR0Stats.end(); it++) {
		cout << "I_" << it-LR0Stats.begin() << " : " << endl;
		for (auto i = it->items.begin(); i != it->items.end(); i++) 
			printf("\t%c %s %d\n", pro[i->pid].left, pro[i->pid].right.c_str(), i->pos);
	}

	for (int i = 0; i < LR0Stats.size(); i++)
		for (auto ch = terminal.begin(); ch != terminal.end(); ch ++) {
			char c = *ch;
			if (action[i][c] != ERROR) 
				printf("action[%d][%c] = %c%d\n", i,c,action[i][c]>0?'s':'r', action[i][c]);
		}
	for (int i = 0; i < LR0Stats.size(); i++)
		for (auto ch = nonTerminal.begin(); ch != nonTerminal.end(); ch ++) {
			if (GOTO[i][*ch] == ACCEPT) printf("GOTO[%d][%c] = acc\n", i, *ch);
			else if (GOTO[i][*ch] != ERROR) printf("GOTO[%d][%c] = %d\n", i, *ch, GOTO[i][*ch]);
		}
	
}
int main()
{
	init();
	output();
	parser();
	return 0;
}
