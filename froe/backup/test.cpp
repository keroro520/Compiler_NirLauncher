#include <stdio.h>
int max(int a, int b) {
	return a > b ? a : b;
}
int func( int a, int b, int (*p)(int,int) ) {
	return (*p)(a,b);
}
void hello() {
	printf("hello world\n");
}
int main() {
	int (*p)(int,int) ;
	int a, b;
	void (*f)(void);
	f = hello;
	(*f)();
	p = max;

	scanf("%d %d", &a, &b);
	printf("%d\n", (*p)(a,b));
	printf("%d\n", func(a,b,p));
	return 0;
}
