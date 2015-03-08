#include "solver.h"
#include <memory>

Solver::Solver()
{
    cout << "Give the integer value of row no of the Matrix A\n";
    cin >> rowNo;
    cout << "Give the integer value of column no of the Matrix A\n";
    cin >> columnNo;
    cout << "[Solver] Allocating the space for solver\n";
    A = new (nothrow) double* [rowNo];
    if (!A)
    {   
        cout << "[Solver ERROR] Memory can't be allocated\n";
        exit(2);
    }

    for ( int i = 0; i < rowNo ; i++)
    {
        A[i] = new (nothrow) double[columnNo];
        if (!A[i])
        {
            cout << "[Solver ERROR] Memory can't be allocated\n";
            delete[] A;
            exit(2);
        }
    }
    b = new (nothrow) double [rowNo];
    C = new (nothrow) double [columnNo];
    x = new (nothrow) double [columnNo];
    if (b == NULL || C == NULL)
    {
        cout << "[Solver ERROR] Memory can't be allocated\n";
        exit(2);
    }
    cout << "[Solver] Space Allocated\n";
    for (int i = 0; i < rowNo; i++)
    {
        for (int j = 0; j < columnNo; j++)
        {
            cout << "give the value of A_" << i << "_" << j<<": ";
            cin >> A[i][j];
        }
    }
    for (int i =0 ; i < rowNo; i++)
    {
        cout << "Give the value of b_" << i <<": ";
        cin >> b[i];
    }
    for (int i =0 ; i < columnNo; i++)
    {
        cout << "Give the value of C_" << i <<": ";
        cin >> C[i];
    }

}

Solver::Solver(int m, int n)
{
    rowNo = m;
    columnNo = n;
    cout << "[Solver] Allocating the space for solver\n";
    A = new double * [rowNo];
    for ( int i = 0; i < rowNo ; i++)
    {
        A[i] = new double[columnNo];
        if ( A[i] == NULL)
        {
            cout << "[Solver ERROR] Memory can't be allocated\n";
            exit(2);
        }
    }
    b = new (nothrow) double [rowNo];
    C = new (nothrow) double [columnNo];
    x = new (nothrow) double [columnNo];
    if (b == NULL || C == NULL || x == NULL)
    {
        cout << "[Solver ERROR] Memory can't be allocated\n";
        exit(2);
    }
    cout << "[Solver] Space Allocated\n";
    for (int i = 0; i < rowNo; i++)
    {
        for (int j = 0; j < columnNo; j++)
        {
            cout << "give the value of A_" << i << "_" << j<<": ";
            cin >> A[i][j];
        }
    }
    for (int i =0 ; i < rowNo; i++)
    {
        cout << "Give the value of b_" << i <<": ";
        cin >> b[i];
    }
    for (int i =0 ; i < columnNo; i++)
    {
        cout << "Give the value of C_" << i <<": ";
        cin >> C[i];
    }
}

Solver::Solver(int m ,int n,double **A_tmp,double *b_tmp,double *C_tmp)
{
    rowNo = m;
    columnNo = n;
    A = A_tmp;
    b = b_tmp;
    C = C_tmp;
}

void Solver::print()
{
    cout << "\nTo Minimise\n\n";
    for(int i =0 ;i<columnNo-1;i++)
    {
        cout << C[i]<<"x_" << i << " +";
    }
    cout << C[columnNo-1] <<"x_" << columnNo-1 << endl << endl;
    cout << "Constrain:\n\n";
    for (int i =0 ;i < rowNo;i++)
    {
        for (int j= 0; j <columnNo-1;j++)
        {               
            cout << A[i][j]<<"x_" << j << " +";
        }  

        cout << A[i][columnNo-1] <<"x_" << columnNo-1<<" <= " << b[i]
            << endl;
    }
    cout << endl << endl;
}

int  Simplex_solver::checkZeroFeasibility()
{
    int flag = 1;
    for (int i= 0;
    return flag;
}
void Simplex_solver::solve()
{
    if (checkZeroFeasibility() == 1)
    {
        allocate_tableau();
        assign_tableau();
        int k =0;
        while ( true)
        {
            k++;
            cout << "[Simplex_solver] Iteration No: " << k << endl;
            pivot_search();
            if (pivot.column == -1 || pivot.row == -1) break;
            //     cout << pivot.row <<" "<< pivot.column<< endl;
            pivot_operation();
            printtableau();
        }
        initializeAnswer();
    }
    else
    {
        cout << "The problem doesn't have a fesible solution at zero \n";
    }
}

void Simplex_solver::initializeAnswer()
{

    x = new (nothrow) double [columnNo+rowNo];
    Z = tableau [0][tableauColumnNo-1];
    for (int i =0 ; i < columnNo+rowNo; i++)
    {
        int index = -1;
        int flag = 0;
        for (int j =0 ; j<rowNo;j++)
        {
            if (tableau[j+1][i+1] == 1) 
            {
                flag++;
                index = j+1;
            }
            else
            {
                if (tableau[j+1][i+1] != 0) flag++;
            }
        }
        if (flag == 1)
        {
            x[i] = tableau[index][tableauColumnNo-1];
        }
        else
        {
            x[i] = 0;
        }
    } 
    cout << "\nThe solution to simplex problem is\n";
    for (int i =0 ; i < rowNo+columnNo;i++)
    {
        cout <<" x_" << i << " = " << x[i] << endl;
    }
    cout <<" Z = " << Z << endl;
}

void Simplex_solver::pivot_operation()
{
    row_divide(pivot.row,tableau[pivot.row][pivot.column]);
    for (int i =0 ; i < tableauRowNo;i++)
    {
        if ( i != pivot.row)
        {
            row_addition(i,pivot.row,-tableau[i][pivot.column]);
        }
    }
}
void Simplex_solver::pivot_search()
{
    int max_index;
    double max;
    max_index = 1;
    max = tableau[0][1];
    for(int i = 2 ; i<tableauColumnNo-1;i++)
    {
        if ( max < tableau[0][i])
        {
            max_index = i;
            max = tableau[0][i];
        }
    }
    if (max <= 0)
    {
        pivot.column = -1;
        return;
    }
    pivot.column = max_index;
    double min;
    double temp;
    int min_index;
    min_index = -1;
    min = tableau[1][tableauColumnNo-1]/tableau[1][pivot.column];
    if (min < 0)
    {
        min = 100000000000000000000.0;
    }
    for (int i =1 ; i < tableauRowNo;i++)
    {
        temp = tableau[i][tableauColumnNo-1]/tableau[i][pivot.column];
        if (temp > 0)
        {
            if (temp <= min)
            {
                min = temp;
                min_index = i;
            }
        }

    }
    pivot.row = min_index;
}
void Simplex_solver::allocate_tableau()
{
    tableauRowNo = rowNo+1;
    tableauColumnNo = rowNo+columnNo+2;
    tableau = new (nothrow) double* [tableauRowNo];
    if (!tableau)
    {
        cout << "[Simplex_solver ERROR] Memory can't be allocated\n";
        exit(2);
    }
    for ( int i = 0; i < tableauRowNo ; i++)
    {
        tableau[i] = new (nothrow) double[tableauColumnNo];
        if (!tableau[i])
        {
            cout << "[Simplex_solver ERROR] Memory can't be allocated\n";
            delete[] tableau;
            exit(2);
        }
    }
}

void Simplex_solver::assign_tableau()
{
    tableau[0][0] = 1;
    for (int i=1;i<tableauRowNo;i++)
    {
        tableau[i][0] = 0;
    }
    for (int i = 1; i < 1+columnNo;i++)
    {
        tableau[0][i] = -C[i-1];
    }

    for (int i = 1; i < tableauRowNo;i++)
    {
        for (int j =1 ; j < (1+columnNo);j++)
        {
            tableau[i][j]=A[i-1][j-1];
        }
    }

    for (int i = 1; i < tableauRowNo;i++)
    {
        for (int j =1+columnNo ; j < tableauColumnNo-1 ;j++)
        {
            tableau[i][j]=0;
            if ( i - 1 == j -1 -columnNo) tableau[i][j]=1;
        }
    }

    for (int i = 1; i <tableauRowNo;i++)
    {
        tableau[i][tableauColumnNo-1] = b[i-1];
    }
    printtableau();
}

void Simplex_solver::printtableau()
{
    for (int i = 0; i < tableauRowNo;i++)
    {
        for (int j =0 ; j < tableauColumnNo;j++)
        {
            cout << tableau[i][j] <<" ";
        }
        cout << endl;
    }
}

void Simplex_solver::row_divide(int row, double param)
{
    for (int i =0 ; i < tableauColumnNo;i++)
    {
        tableau[row][i] = tableau[row][i]/param;
    }
}

void Simplex_solver::row_addition(int row1,int row2,double param)
{
    for (int i =0 ; i < tableauColumnNo;i++)
    {
        tableau[row1][i] = tableau[row1][i]+ tableau[row2][i]*param;
    }
}

