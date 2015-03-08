#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <stdlib.h>
#include <new>
using namespace std;
class Solver
{
    protected:
    /*
     * This class initializes the solver for solving the optimisation problem"
     */
    long long int rowNo;
    long  long int columnNo;
    double **A;
    double *b;
    double *C;
    double *x;
    double  Z;
    public:
    Solver();
    Solver(int m,int n);
    Solver(int m ,int n,double **A_tmp,double *b_tmp,double *C_tmp);
    void print();
};

class Integer_solver: public Solver
{
    public:
    void solve();
};

class Simplex_solver:public Solver
{
    double **tableau;
    int tableauRowNo;
    int tableauColumnNo;
    void allocate_tableau();
    void assign_tableau();
    void pivot_search();
    void row_divide(int row,double param);
    void row_addition(int row1,int row2,double param);
    void printtableau();
    void pivot_operation();
    struct Pivot
    {
        int row;
        int column;
    };
    Pivot pivot;
    void initializeAnswer();
    public:
    void solve();
};
#endif
