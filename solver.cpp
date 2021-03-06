#include "solver.h"

double abs(double x)
{
    if (x < 0) return -x;
    return x;
}

Solver::Solver()
{
    flagSolver = 0;
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
    flagSolver =0;
    rowNo = m;
    columnNo = n;
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

Solver::Solver(int m ,int n,double **A_tmp,double *b_tmp,double *C_tmp)
{
    flagSolver = 0;
    rowNo = m;
    columnNo = n;
    A = A_tmp;
    b = b_tmp;
    C = C_tmp;
}

double Solver::get_answer(double *x_new)
{
    for (int i =0 ; i < columnNo;i++)
    {
        x_new [i] = x[i];
    }
    return Z; 
}
void Solver::print()
{
    cout << "\nTo Minimise\n\n";
    for(int i =0 ;i<columnNo-1;i++)
    {
        cout << C[i]<<"x_" << i << " + ";
    }
    cout << C[columnNo-1] <<"x_" << columnNo-1 << endl << endl;
    cout << "Constrain:\n\n";
    for (int i =0 ;i < rowNo;i++)
    {
        for (int j= 0; j <columnNo-1;j++)
        {               
            cout << A[i][j]<<"x_" << j << " + ";
        }  

        cout << A[i][columnNo-1] <<"x_" << columnNo-1<<" <= " << b[i]
            << endl;
    }
    cout << endl << endl;
}

void Solver::check_answer()
{
    for (int i =0 ; i < rowNo;i++)
    {
        double sum = 0;
        for (int j =0; j <columnNo;j++)
        {
            sum += x[j]*A[i][j];
        }
        if (sum > b[i])
        {
            solutionFlag = -1;
            return;
        }
    }
    solutionFlag = 1;
}

int  Simplex_solver::checkZeroFeasibility()
{
    cout << "[Simplex Solver] Checking Zero Feasibility\n";
    int flag = 0;
    for (int i =0 ; i < rowNo; i++)
    {
        if (b[i] < 0)
        {
            flag++;
        }
    }
    if (flag > 0)
    {
        cout << "[Simplex_solver]The problem doesn't have a fesible solution at zero \n";
        cout <<"[Simplex_solver]Using two Phase simplex to solve the problem\n";

        int newRowNo = rowNo+1;
        int newColumnNo = columnNo + flag;
        Simplex_solver tmp(newRowNo,newColumnNo,NULL,NULL,NULL);
        tmp.flagSolver = 2;
        tmp.allocate_tableau();
        tmp.tableau[0][0]= 1;
        for (int i =1; i <tmp.tableauRowNo;i++)
        {
            tmp.tableau[i][0] = 0;
        }
        for (int i = 1; i < columnNo+1;i++)
        {
            tmp.tableau[0][i] = 0;
            tmp.tableau[1][i] = -C[i-1];
        }
        for (int i = 1+columnNo; i < 1+columnNo+rowNo;i++)
        {
            tmp.tableau[0][i] = 0;
            tmp.tableau[1][i] = 0;
        }
        for (int i = 1+columnNo+rowNo; i < tmp.tableauColumnNo-1;i++)
        {
            tmp.tableau[0][i] = 1;
            tmp.tableau[1][i] = 0;
        }
        tmp.tableau[0][tmp.tableauColumnNo-1]=0;
        tmp.tableau[1][tmp.tableauColumnNo-1]=0;
        for (int i =2; i <tmp.tableauRowNo;i++)
        {
            tmp.tableau[i][tmp.tableauColumnNo-1] = b[i-2];
            if (b[i-2] < 0)
            {
                tmp.tableau[i][tmp.tableauColumnNo-1] = -b[i-2];
            }
        }
        for (int i =0; i < rowNo;i++)
        {
            int multiplier = 1;
            if (b[i] < 0) multiplier = -1;
            for (int j=0;j<columnNo;j++)
            {
                tmp.tableau[i+2][j+1] = multiplier*A[i][j];
            }
        }
        for (int i = 0; i < rowNo; i++)
        {
            for (int j=0;j<rowNo+flag;j++)
            {
                tmp.tableau[i+2][j+1+columnNo] = 0;
                if ( i == j ) 
                {

                    tmp.tableau[i+2][j+1+columnNo] =1;
                    if (b [i] <0)
                        tmp.tableau[i+2][j+1+columnNo] =- 1;
                }
            }
        }
        int k = columnNo+rowNo+1;
        for (int i =2 ;i<tmp.tableauRowNo;i++)
        {
            if (b[i-2] < 0)
            {
                tmp.tableau[i][k++] = 1;
            }
        } 
        tmp.flagSolver =1;
        tmp.solve();
        int cRow = -1;
        int cColumn = -1;
        for (int i =rowNo+columnNo+1; i < tmp.tableauColumnNo-1;i++ )
        {
            int rflag =0;
            cColumn = 1; 
            for (int j = 2 ; j < tmp.tableauRowNo;j++)
            {
                if (abs(tmp.tableau[j][i]) >  10e-7) 
                {
                    rflag++;
                    cRow = j; 
                }
            }
            
            cout << "rflag " << rflag << endl;
            if (rflag == 1)
            {
                while(tmp.tableau[cRow][cColumn++] == 0 && cColumn < rowNo+columnNo+1  )
                {
                    cout << cRow << " " <<cColumn<<endl;
                } 
                if (cColumn < rowNo+columnNo+1) 
                {
                    tmp.pivot_operation(cRow,cColumn-1);
                }
            }
        }
        tableau[0][0] = 1;
        for (int i = 1; i < tableauRowNo;i++)
        {
            tableau[i][0] = 0;
        }
        for (int i =0 ; i<rowNo+1 ;i++)
        {
            for (int j =0 ; j < tableauColumnNo-1; j++)
            {
                tableau[i][j+1] = tmp.tableau[i+1][j+1];
            }
            tableau[i][tableauColumnNo-1] = tmp.tableau[i+1][tmp.tableauColumnNo-1];
        }
    }
    return flag;
}

void Simplex_solver::solve()
{
    if ( flagSolver !=1)
    {
        allocate_tableau();
        if (checkZeroFeasibility() == 0)
        {
            allocate_tableau();
            assign_tableau();
        }
    }
    int k =0;
    while ( true)
    {
        k++;
        cout << "[Simplex_solver] Iteration No: " << k << endl;
        pivot_search();
        if (pivot.column == -1 || pivot.row == -1 ) break;
        pivot_operation();
        cout << endl;
    }
    printtableau();
    if (flagSolver !=1)
    {
        initializeAnswer();
    }
}

void Simplex_solver::initializeAnswer()
{
    x = new (nothrow)double [columnNo+rowNo];
    int *tmpstack; 
    tmpstack = new (nothrow)int [columnNo+rowNo];
    Z = tableau [0][tableauColumnNo-1];
    for (int i =0 ; i < columnNo+rowNo; i++)
    {
        int index = -1;
        int flag = 0;
        for (int j =0 ; j<rowNo+1;j++)
        {
            if (tableau[j][i+1] == 1) 
            {
                flag++;
                index = j;
            }
            else
            {
                if (tableau[j][i+1] != 0) flag++;
            }
        }
        for (int k =0;k < i;k++)  
        {
            if (index == tmpstack[k]) flag = -1;
        }
        if (flag == 1 && index >0)
        {
            x[i] = tableau[index][tableauColumnNo-1];
            tmpstack[i] = index;
        }
        else
        {
            x[i] = 0;
            tmpstack[i] = -1;
        }
    }
    check_answer();
    if (solutionFlag < 0)
    {
        cout << "[Simplex_solver] Maybe the Solution doesn't exist\n " ;
        return;
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
    if ( abs(tableau[pivot.row][pivot.column]) >10e-7)
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
}

void Simplex_solver::pivot_operation(int a,int b)
{
    pivot.row = a;
    pivot.column  = b;

    if ( abs(tableau[pivot.row][pivot.column]) > 10e-7)
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
}

struct list
{
    double value;
    int index;
    list *next;
};
void Simplex_solver::pivot_search()
{
    list stack;
    list *temp =NULL;
    list *current =NULL;
    stack.next = NULL;
    stack.index = -1;
    stack.value = 1;
    for(int i = 1 ; i<tableauColumnNo-1;i++)
    {

        temp = new list;
        if (tableau[0][i] > 10e-7)
        {
            temp->index = i;
            temp->value = tableau[0][i];
            temp->next = NULL;

            current = &stack;
            while (current->next != NULL)
            {
                if (temp->value >= current->next->value)
                {
                    temp->next = current->next;
                    break ;
                }
                current = current->next;

            }
            current->next = temp;
        }

    }
    current = &stack;

    while (current->next != NULL)
    {
        current = current->next;
        pivot.column = current->index;
        double min;
        double temp2;
        int min_index;
        min_index = -1;
        min = 100000000000000000000.0;
        for (int i =1 ; i < tableauRowNo;i++)
        {
            temp2 = tableau[i][tableauColumnNo-1]/tableau[i][pivot.column];
            if (temp2 >= 0)
            {
                if (temp2 <= min)
                {
                    min = temp2;
                    min_index = i;
                }
            }
        }
        pivot.row = min_index;
        if (pivot.row > 0) 
        {
            return;
        }
    }
    pivot.column = -1;
    return;
}
void Simplex_solver::allocate_tableau()
{
    tableauRowNo = rowNo+1;
    tableauColumnNo = rowNo+columnNo+2;
    if (flagSolver == 2)
    {
        tableauColumnNo--;
    }
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
    int start = 1;
    if (flagSolver == 2) start =2;
    for (int i = start; i < tableauRowNo;i++)
    {
        for (int j =1+columnNo ; j < tableauColumnNo-1 ;j++)
        {
            tableau[i][j]=0;
            if ( i - start == j -1 -columnNo) tableau[i][j]=1;
        }
    }

    for (int i = 1; i <tableauRowNo;i++)
    {
        tableau[i][tableauColumnNo-1] = b[i-1];
    }
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

