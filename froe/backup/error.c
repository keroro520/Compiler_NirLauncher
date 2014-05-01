#include <stdio.h>
#include <stdlib.h>
#include "error.h"

//void lexError(const char * s)
//{
//	fprintf(stderr, "%s : %s %d\n", s, __FILE__, __LINE__);
//	exit(0);
//}
void lexError(const char * s, char * s2)
{
	fprintf(stderr, "%s : %s  in %s %d\n", s, s2, __FILE__, __LINE__);
	exit(0);
}
//void lexError(const char * s, char ch)
//{
//	fprintf(stderr, "%s : %c  in %s %d\n", s, ch, __FILE__, __LINE__);
//	exit(0);
//}
