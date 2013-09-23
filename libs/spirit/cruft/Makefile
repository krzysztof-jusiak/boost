.PHONY : t2

t2 : t2_32 t2_64

t2_32 : t2.cpp
	clang++ -m32 -std=c++11 -I../../.. -g -o $@ $^

t2_64 : t2.cpp
	clang++ -std=c++11 -I../../.. -g -o $@ $^

t3 : t3.cpp
	g++ -m32 -std=c++11 -I../../.. -g -o $@ $^
