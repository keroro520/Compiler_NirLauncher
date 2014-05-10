#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "environment.hpp"

char * strTable[1984];

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
