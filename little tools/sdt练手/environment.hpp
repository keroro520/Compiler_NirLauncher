#ifndef			__SYMTABLE_HPP__
#define			__SYMTABLE_HPP__

typedef			int			Refer ;

class Node ;
void updateEnv(Node * a, int val) ;
int lookup(int i) ;

Refer  str2ref(const char * ) ;
char * ref2str(Refer i) ;
int    stoi(char * );


extern bool boo[1984];
extern int  env[1984];
extern char * strTable[1984];

#endif
