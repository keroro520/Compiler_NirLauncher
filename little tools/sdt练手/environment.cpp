#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "environment.hpp"
#include "structure.hpp"

char * strTable[1984];
bool boo[1984] = {0};
int  env[1984];

void updateEnv(Node * a, int val)
{
    env[a->val] = val ;
    boo[a->val] = true;
}

int lookup(int i)
{
    if (boo[i] == false) {
        fprintf(stderr, "未定义变量 %s\n", ref2str(i));
        exit(0);
    }
    return env[i];
}

Refer str2ref(const char * s)
{
	int i;
	for (i = 0; strTable[i]; i++) {
		if (strcmp(s, strTable[i]) == 0) return i ;
	}
	if (i >= 1984) {
		fprintf(stderr, "Out of space");
		exit(0);
	}

	strTable[i] = (char *) malloc(sizeof (char) * (1 + strlen(s)));
	strcpy(strTable[i], s);
	return i;
}

char * ref2str(Refer i)
{
	return strTable[i];
}

int stoi(char * s)
{
	int t = 0;
	while(*s) {
		t = t * 10 + (*s - '0');
		s++;
	}
	return t;
}
