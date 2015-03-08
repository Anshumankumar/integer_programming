all:solver

solver:main.o solver.o
	g++ main.o solver.o -o solver

main.o:main.cpp
	g++ -c main.cpp

solver.o:solver.cpp
	g++ -c solver.cpp

clean:
	rm *.o
	rm solver
