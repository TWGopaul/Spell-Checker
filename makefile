# Travis Gopaul
# Makefile for Project 2
program: main.o Dictionary.o LinkedList.o
	g++ -g -std=c++11 main.o Dictionary.o LinkedList.o -o main
main.o: main.cpp
	g++ -g -std=c++11 -c main.cpp
Dictionary.o: Dictionary.cpp LinkedList.cpp
	g++ -g -std=c++11 -c Dictionary.cpp LinkedList.cpp
LinkedList.o: LinkedList.cpp
	g++ -g -std=c++11 -c LinkedList.cpp
clean:
	rm -f *.o
	rm -f main
val:
	make
	valgrind ./main
leak:
	make
	valgrind --leak-check=full ./main
