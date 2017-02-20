all: test

test: main.o normalize.o
	g++ main.o normalize.o -o test

main.o: main.cpp
	g++ -c main.cpp

normalize.o: normalize.cpp
	g++ -c normalize.cpp

clean: 
	rm -rf *.o test

