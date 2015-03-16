all:solver

solver:main.o solver.o integer_solver.o
	g++ main.o solver.o integer_solver.o -o solver

main.o:main.cpp
	g++ -c main.cpp

solver.o:solver.cpp solver.h
	g++ -c solver.cpp

integer_solver.o:integer_solver.cpp
	g++ -c integer_solver.cpp

clean:
	rm *.o
	rm solver
