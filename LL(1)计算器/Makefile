all:
	clang -std=c11 -Wall -g *.c -o Froe
release:
	clang -std=c11 -O2 -Wall -g *.c -o Froe
profile:
	gcc -std=c11 -pg -Wall -g *.c -o Froe
coverage:
	gcc -std=c11 -fprofile-arcs -ftest-coverage -Wall -g *.c -o Froe
clean :
	rm -f Froe *.gcno *.gcda gmon.out *.gcov

.PHONY : all release profile clean
