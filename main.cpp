#include <iostream>
#include <string>

using namespace std;

void disp_help()
{
    cout << "This program Solves the optimization problem in which all\n"
            "variables are restricted to integer.\n\n"
            "An integer linear program in canonical form is expressed as:\n\n"
            "    maximise  ***   C_transpose.*x   ***\n"
            "    subject to\n"
            "           __________________________\n"
            "          |                          |\n"
            "          |  Ax <= b                 |\n"
            "          |  x > 0                   |\n"
            "          |  x belong to integer,    |\n"
            "          |__________________________|\n";
}

int autosolve(int m,int n)
{
    cout << "Allocating the Space for Solver\n";
    return 0;
}

int solve(int m,int n)
{
    cout << "Allocating the Space for Solver\n";
    return 0;
}

int main(int argc, char** argv )
{
    cout << "Integer Program Solver\n\n"; 
    if (argc == 2)
    {
        string temp = "--help";
        if ( temp.compare(argv[1]) == 0 )
        {
            disp_help();
            return 0;
        }
        temp = "--auto";
        if ( temp.compare(argv[1]) == 0 )
        {
            return autosolve(20,10);
            
        }
        else
        {
            cout << "Unknown Args \n";
            return 1;
        }
    }
    if (argc == 4)
    {
        string temp = "--auto";
        if ( temp.compare(argv[1]) == 0 ) 
        {
            return autosolve(20,10);
        }
    }
    else
    {
        int m;
        int n;
        cout << "Enter the no of rows in matrix A\n";
        cin >> m;
        cout << "Enter the no of columns in matrix A\n";
        cin >> n;
        return solve(m,n);
    }
    return 0;
}
