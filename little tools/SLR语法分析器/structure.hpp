#ifndef		__STRUCTURE_H__
#define		__STRUCTURE_H__
#include <vector>
#include <string>
#include <algorithm>
#include <set>

#define		for_each(i, c)		for (auto i = (c).begin(); i != (c).end(); i++) 

template<class T, class T2> bool IN(T C, T2 x)
{
	return std :: find(C.begin(),C.end(),x) != C.end();
}

class Product {
	public :
	char left;
	std :: string right;
	Product () : right("") { }
	Product (char left, char c) : left(left) {
		right = "";
		right += c;
	}
} ;

class Item {				//(product . position)
	public :
	int pid;				//productID
	int pos;
	Item () : pos(0) { }
	Item (int pid, int pos) : pid(pid), pos(pos) { }
	bool operator == (Item b) {
		return pid == b.pid && pos == b.pos;
	}
} ;

class ItemSet {
	public :
	std :: vector<Item> items;
	ItemSet () { }
	ItemSet (Item item) {
		items.push_back(item) ;
	}
	bool operator == (ItemSet b) {
		if (items.size() != b.items.size()) return false;
		for (auto i = items.begin(), j = b.items.begin(); i != items.end() ; i++, j++) {
			if (!(*i == *j)) return false;
		}
		return true;
	}
} ;




extern char null ;
extern char eof  ;
extern char beginSymbol ;

extern std :: vector<Product> pro;
extern std :: set <char> terminal, nonTerminal, symbol;
extern std :: set<char> nullSet, eofSet;
extern std :: set <char> first[256];
extern std :: set <char> follow[256];

extern std :: vector<ItemSet> LR0Stats;
extern int GOTO[1984][1984];
extern int action[1984][1984];
extern int ACCEPT;
extern int ERROR;

#endif
