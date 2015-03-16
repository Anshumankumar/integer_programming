#include "integer_solver.h"
Integer_solver::Integer_solver(double *Z_star):Solver()
{
    if (Z_star == NULL)
    {
        Z_optimum = new double;
        *Z_optimum = INFINITY;
    }
    else
    { 
        Z_optimum = Z_star;
    }

}

Integer_solver::Integer_solver(int m ,int n,double **A_tmp,double *b_tmp,
        double *C_tmp, double *Z_star):Solver(m,n,A_tmp,b_tmp,C_tmp)
{
    if (Z_star == NULL)
    {
        Z_optimum = new double;
        *Z_optimum = INFINITY;
    }
    else
    { 
        Z_optimum = Z_star;
    }
}

void Integer_solver::solve()
{
    Simplex_solver simSolver(rowNo,columnNo,A,b,C);
    simSolver.print();
    simSolver.solve();
    x = new (nothrow) double [columnNo];
    if (simSolver.solutionFlag < 0)
    {
        solutionFlag == -1;
        cout << "[Integer_solver] No feasible Solution\n";
        return;
    }
    else
    {
        Z = simSolver.get_answer(x);
    }
    for (int i =0 ; i < columnNo;i++)
    {
        if (x[i] != (int) x[i])
        {
            create_sub_problem(i);
            break;
        }  
    }

    if (solutionFlag < 0)
    {
        cout << "[Integer_solver] No feasible Solution\n";
        return; 
    }
    check_answer(); 
    if (solutionFlag < 0)
    {
        cout << "[Integer_solver] No feasible Solutioni\n";
        return; 
    }
    Z = (int)Z;
    if (*Z_optimum < Z)
    {
        cout << "[Integer_solver] Already have better solution\n";
        solutionFlag = -1;
        return;
    }
    cout << "\n\n\n\n\n[Integer_solver ] Solution Exist\n";

    solutionFlag = 1;
    for (int i =0; i < columnNo;i++)
    {   
        cout << "x_" << i << " = " << x[i] << endl;
    }
    cout <<"Z = " << Z << endl;
    return;
}
void Integer_solver::create_sub_problem(int param)
{
    cout << "[Integer_solver] Branching \n";
    int newRowNo = rowNo +1;
    double **A_new1;
    double **A_new2;
    double *b_new2;
    double *b_new1;
    A_new1 = new (nothrow) double* [newRowNo];

    if (!A_new1)
    {
        cout << "[Integer_solver ERROR] Memory can't be allocated\n";
        exit(2);
    }

    for ( int i = 0; i < newRowNo ; i++)
    {
        A_new1[i] = new (nothrow) double[columnNo];
        if (!A_new1[i])
        {
            cout << "[Integer_solver ERROR] Memory can't be allocated\n";
            delete[] A_new1;
            exit(2);
        }
    }

    A_new2 = new (nothrow) double* [newRowNo];
    if (!A_new2)
    {
        cout << "[Solver ERROR] Memory can't be allocated\n";
        exit(2);
    }

    for ( int i = 0; i < newRowNo ; i++)
    {
        A_new2[i] = new (nothrow) double[columnNo];
        if (!A_new2[i])
        {
            cout << "[Solver ERROR] Memory can't be allocated\n";
            delete[] A_new2;
            exit(2);
        }
    }    
    b_new1 = new (nothrow) double [newRowNo];
    b_new2 = new (nothrow) double [newRowNo];
    for (int i = 0; i < rowNo; i++)
    {
        b_new1[i] = b[i];
        b_new2[i] = b[i];
        for ( int j =0 ; j < columnNo;j++)
        {
            A_new1[i][j] = A[i][j];
            A_new2[i][j] = A[i][j];
        }
    }
    b_new1[rowNo] = (int)x[param];
    b_new2[rowNo] = -((int)x[param]+1);
    for  (int i = 0; i < columnNo;i++)
    {
        A_new1[rowNo][i] =0;
        A_new2[rowNo][i] =0;
    }
    A_new1[rowNo][param] = 1;
    A_new2[rowNo][param] = -1;
    Integer_solver solver1(newRowNo,columnNo,A_new1,b_new1,C,Z_optimum);
    Integer_solver solver2(newRowNo,columnNo,A_new2,b_new2,C,Z_optimum);
    solver1.solve();
    if (solver1.solutionFlag < 0 && solver2.solutionFlag < 0)
    {
        solutionFlag = -1;
        return;
    }
    solver2.solve();
    if (solver1.solutionFlag >0)
    {
        *Z_optimum = solver1.get_answer(x);
         Z = *Z_optimum;

    }

    if (solver2.solutionFlag >0)
    {
        *Z_optimum = solver2.get_answer(x);
        Z =*Z_optimum;
    }
}
