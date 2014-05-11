#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <set>
#include "structure.hpp"
#include "init.hpp"
using namespace std;

char null;
char eof ;
char beginSymbol;

set<char> nullSet, eofSet;

vector<Product> pro;
set <char> terminal, nonTerminal, symbol;
set <char> first[256];
set <char> follow[256];

vector<ItemSet> LR0Stats;						// 规范LR(0)项集族
int GOTO[1984][1984];
int action[1984][1984];							//Action表
int ACCEPT;
int ERROR;										//0xffffffff ?

void analizeProduct(FILE * f)
{
	char c = ' ';
	while (true) {
		while ( isspace(c = getc(f)) ) ;
		if (c == EOF) break;

		Product p ; 

		if (beginSymbol == ' ') {
			beginSymbol = 'S';
			pro.push_back(Product('S', c));
		}

		p.left = c;
		while ( (c = getc(f)) != ':' ) ;
		while (true) {
			while ((c = getc(f)) == ' ' || c == '\t') ;
			if (c == '\n' || c == EOF) break;
			p.right += c;
		}

		pro.push_back(p);
		nonTerminal.insert(p.left);
		for_each(it, p.right) {
			if (!isupper(*it)) terminal.insert(*it);
		}
	}
	nonTerminal.insert( beginSymbol = 'S');
	terminal.insert(null);
	terminal.insert(eof);
	symbol = terminal;
	symbol.insert(nonTerminal.begin(), nonTerminal.end());
}

void getFirstSet()
{
	for_each(it, terminal) {
		first[*it].insert(*it);
	}
	first[null].insert(null);
	first[eof].insert(eof);

	bool flag = true;
	while (flag) {
		flag = false;
		for_each (p, pro) {
			set<char> rhs ;
			set_difference(first[p->right[0]].begin(), first[p->right[0]].end(),
						   nullSet.begin(), nullSet.end(),
						   insert_iterator<set<char> >(rhs,rhs.begin()));
			auto it = p->right.begin() ;
			for ( ++it; it != p->right.end() && first[*it].find(null) != first[*it].end(); it++) {
				rhs.insert(first[*it].begin(), first[*it].end());
				rhs.erase(null);
			}

			if (it == p->right.end() && first[*it].find(null) != first[*it].end()) {
				rhs.insert(null);
			}
			int tmp = first[p->left].size();
			first[p->left].insert(rhs.begin(), rhs.end());
			if (tmp != first[p->left].size()) flag = true;
		}
	} ;
}

void getFollowSet()
{
	follow[beginSymbol].insert(eof);
	bool flag = true;
	while (flag) {
		flag = false;
		for_each (p, pro) {
			set<char> trailer = follow[p->left];
			for (int i = p->right.length() - 1; i >= 0; i--) {
				char ch = p->right[i];
				if (isupper(ch)) {
					int tmp = follow[ch].size();
					follow[ch].insert(trailer.begin(), trailer.end());
					if (tmp != follow[ch].size()) flag = true;

					if (first[ch].find(null) != first[ch].end()) {
						trailer.insert(first[ch].begin(), first[ch].end());
						trailer.erase(null);
					} else {
						trailer = first[ch];
					}
				} else {
					trailer = first[ch];
				}
			}
		}
	}
}

ItemSet closure(ItemSet I)
{
	for (int i = 0; i < I.items.size(); i++) {
		string & s = pro[I.items[i].pid].right;
		if ( IN(nonTerminal, s[I.items[i].pos]) ) {
			for_each(p, pro) {
				if (p->left == s[I.items[i].pos] && !IN(I.items, Item(p-pro.begin(),0))) {
					I.items.push_back(Item(p-pro.begin(),0));
				}
			}
		}
	}
	return I;
}

ItemSet _goto(ItemSet I, char X)
{
	ItemSet J;
	for_each (i, I.items) {
		if (i->pos < pro[i->pid].right.length() && pro[i->pid].right[i->pos] == X) {
			J.items.push_back(Item(i->pid, i->pos+1));
		}
	}
	return J;
}

void buildItemSetClue () 
{
	memset(GOTO, 128, sizeof GOTO);
	vector<ItemSet> &C = LR0Stats;
	C.push_back( closure(ItemSet(Item(0, 0))) );

	int cdr = 0;
	while (cdr < C.size()) {
		ItemSet I = C[cdr++];
		for_each (ch, symbol) {
			char X = *ch;
			ItemSet newI = closure(_goto(I,X));
			if (newI.items.size() > 0 && !IN(C,newI)) {
				C.push_back(newI);
			}
			if (newI.items.size() > 0) GOTO[cdr-1][X] = find(C.begin(), C.end(), newI) - C.begin();
		}
	}
}

void getActionTable()
{
	memset(&ERROR,  128, sizeof (int));
	ACCEPT = ERROR + 1;

	for (int i = 0; i < LR0Stats.size(); i++) {
		for_each(ch, symbol) {
			action[i][*ch] = ERROR;
		}
	}

	for_each (I, LR0Stats) {
		int stat = I - LR0Stats.begin();
		for_each (i, I->items) {
			Product &p = pro[i->pid];
			string  &s = p.right;
				
			if (i->pos < s.length() && !isupper(s[i->pos])) {
				char   ch  = s[i->pos];
				action[stat][ch] = GOTO[stat][ch];
			} else if (i->pos == s.length()) {
				for_each (a, follow[p.left]) {
					action[stat][*a] = -i->pid;
				}
			}
		}

		if (IN(I->items, Item(0,1))) {
			action[stat][eof] = ACCEPT;
		}
	}
}

void init()
{
	null = '@';
	eof  = '$';
	beginSymbol = ' ';
	nullSet.insert(null);
	eofSet.insert(eof);

	FILE * f = fopen("grammar.txt", "r");
    analizeProduct(f);
	fclose(f);
    getFirstSet();
    getFollowSet();
    buildItemSetClue () ;
    getActionTable();
}
