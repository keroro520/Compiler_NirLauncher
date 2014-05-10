all:
	g++ -std=c++11  -g *.cpp -o Froe
release:
	g++ -std=c++11 -O2  -g *.cpp -o Froe
profile:
	g++ -std=c++11 -pg  -g *.cpp -o Froe
coverage:
	g++ -std=c++11 -fprofile-arcs -ftest-coverage  -g *.cpp -o Froe
clean :
	rm -f Froe *.gcno *.gcda gmon.out *.gcov

.PHONY : all release profile clean
