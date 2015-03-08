all:solver

solver:main.o
	g++ main.o -o solver

main.o:main.cpp
	g++ -c main.cpp
