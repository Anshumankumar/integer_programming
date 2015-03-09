#ifndef SOLVER_H
#define SOLVER_H
#include <iostream>
#include <stdlib.h>
using namespace std;
class Solver
{
    protected:
        /*
         * This class initializes the solver for solving the optimisation problem"
         */
        int rowNo;
        int columnNo;
        double **A;
        double *b;
        double *C;
        double *x;
        double  Z;
    public:
        Solver();
        int flagSolver; //This is used to handle a special case for two way simplex
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
    void assign_tableau();
    void pivot_search();
    void row_divide(int row,double param);
    void row_addition(int row1,int row2,double param);
    void pivot_operation();
    int checkZeroFeasibility();
    struct Pivot
    {
        int row;
        int column;
    };
    Pivot pivot;
    void initializeAnswer();
    public:
    void solve();
    double **tableau;
    void printtableau();
    void pivot_operation(int a,int b);
    Simplex_solver(int m ,int n,double **A_tmp,double *b_tmp,double *C_tmp):
        Solver(m,n,A_tmp,b_tmp,C_tmp) {}
    Simplex_solver():Solver(){}
    void allocate_tableau();
    int tableauRowNo;
    int tableauColumnNo;

};
#endif
