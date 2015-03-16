#ifndef INTERGER_SOLVER_H
#define INTERGER_SOLVER_H
#include "solver.h"
#include <cmath>
class Integer_solver:public Solver
{
    double* Z_optimum;
    public:
    Integer_solver(int m ,int n,double **A_tmp,double *b_tmp,
            double *C_tmp,double *Z_star);
    Integer_solver(double *);
    void solve();
    void create_sub_problem(int);
};

#endif
