//*******************************************************
//                  HEADER FILE USED IN PROJECT
//*******************************************************
#include <iostream>
#include<fstream>
#include<Windows.h>
#include <cstdlib>
#include<time.h>
#define UNASSIGNED 0
#define size 9
using namespace std;
bool fault[9][9]={false};

//************************************************************
//                         CLASS USED IN PROJECT
//************************************************************
class Sudoku
{
    int grid[size][size];
    bool isSafe(int row, int col, int num); //To check whether the element is inserted in the right place
    bool InRow(int row, int num);//To check whether element to be inserted is already present in the row or not
    bool InBox(int boxStartRow, int boxStartCol, int num);//To check whether element to be inserted is already present in the box or not
    bool InCol(int col, int num);//To check whether element to be inserted is already present in the column or not
    public:
        void clear_fault();
        Sudoku(int b[9][9]); //To initialize the grid
        bool FindUnassignedLocation(int &row, int &col); //Find a location in grid which is empty
        bool SolveSudoku();//To solve the Sudoku
        void replace_ele(int,int,int);//To replace the empty space by the number entered by user
        void printGrid();//To print the required grid
};

void Sudoku::clear_fault()
{
    for (int i = 0; i < size; i++)
        for ( int j= 0; j <size; j++)
            if (fault[i][j])
                grid[i][j]=0;
}

void Sudoku::replace_ele(int a,int b,int num)
{
    if(fault[a-1][b-1]==true)
        grid[a-1][b-1]=num;
    if(!isSafe(a-1,b-1,num))
        fault[a-1][b-1]=true;
    else fault[a-1][b-1]=true;
    if(grid[a-1][b-1]==0)
        grid[a-1][b-1]=num;
}

Sudoku::Sudoku(int b[9][9])
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        grid[i][j]=b[i][j];
}

bool Sudoku::SolveSudoku()
{
    int row, col;
    if (!FindUnassignedLocation(row, col))
        return true;
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;
            if (SolveSudoku())
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

bool Sudoku::FindUnassignedLocation(int &row, int &col)
{
    for (row = 0; row < size; row++)
        for (col = 0; col <size; col++)
            if (grid[row][col] == UNASSIGNED )
                return true;
    return false;
}

bool Sudoku::InRow(int row, int num)
{
    for (int col = 0; col < size; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool Sudoku::InCol(int col, int num)
{
    for (int row = 0; row < size; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool Sudoku::InBox(int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}

bool Sudoku::isSafe(int row, int col, int num)
{
    return !InRow(row, num) && !InCol(col, num) && !InBox(row - row % 3 , col - col % 3, num);
}

void Sudoku::printGrid()
{
    cout<<"\n ";
    for (int row = 0; row < size; row++)
    {
        if(row==3 || row==6 )
        {
            for (int col = 0; col < size; col++)
            {
                HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, FOREGROUND_RED  | FOREGROUND_INTENSITY);
                if(col==3 || col==6 )
                    cout<<"|-";
                    cout<<"---";
            }
            cout<<endl<<" " ;
        }
        HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,FOREGROUND_BLUE | FOREGROUND_GREEN  | FOREGROUND_INTENSITY);
        for (int col = 0; col < size; col++)
        {
            if(col==3 || col==6 )
            {
                HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, FOREGROUND_RED  | FOREGROUND_INTENSITY);
                cout<<"| ";
            }
            HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,FOREGROUND_BLUE | FOREGROUND_GREEN  | FOREGROUND_INTENSITY);
            if(grid[row][col]==0)
            {
                HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
                cout<<grid[row][col]<<"  ";
            }
            else
            {
                HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(h,FOREGROUND_BLUE | FOREGROUND_GREEN  | FOREGROUND_INTENSITY);
                cout<<grid[row][col]<<"  ";
            }
        }
        cout<<endl<<" ";
    }
}

void clear()
{
    system("cls");
}

//***********************************************************
//    				THE MAIN FUNCTION OF PROGRAM
//***********************************************************

int main()
{
    fstream ifile;
    int x=0,y=0,choose;
    ifile.open("C:/Users/sanchi/Desktop/sudo.txt",ios::in);
    int a[9][9],n,posx,posy;
    srand(time(NULL));
    choose=rand()%10;
    if(!ifile)
    {
        cout<<"File not found !!";
    }
    else
    {
        if(choose!=0)ifile.seekp(choose*(81*2)+choose);
        for(int i=0;i<9;++i)
            for(int j=0;j<9;j++)
                ifile>>a[i][j];
                ifile.seekp(1,ios::cur);
    }
    Sudoku b(a);
    char ch;int flag=0;
    do
    {
        clear();
        b.printGrid();
        cout<<"\nEnter the element to be inserted : ";
        cin>>n;
        int f=0;
        cout<<"Enter its position : ";
        cin>>posx>>posy;
        b.replace_ele(posx,posy,n);
        if(!b.FindUnassignedLocation(x,y))
        {
            flag=1;
            for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
                    if(fault[i][j]==true)
                    f++;
            if(f==0)
            cout<<"\n\t\tYou solved it !!\n\t\t    You won !!"<<endl;
            else
                cout<<"\n\t\tYou could not solve it !!\n\t\t     You lost !!"<<endl;
            break;
        }
        else
        {
            cout<<"Do you want to continue : ";
            cin>>ch;
        }
    }while(ch=='y' || ch=='Y');
    if(!flag)
    {
        clear();
        b.clear_fault();
        if (b.SolveSudoku() == true)
          b.printGrid();
        else
            cout<<"No solution exists"<<endl;
        cout<<"\n\t\tYou could not solve it !!\n\t\t You lost !!"<<endl;
    }
    return 0;
}
