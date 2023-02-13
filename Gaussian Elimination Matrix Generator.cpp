#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;
void MatVec(int r, int c, double **A, double*x,double* b);
void Gaussian(double **A, double *x, double *b, int N);
void ShowMat(double **A, int n, int m);
void ShowVec(double *V, int n);
int main()
{
    ifstream fout;
    fout.open("Mat1.txt",ios::out);
    int r, c;
    double **A;
    double *x;
    double *b;
    int answer;
    cout<<"how many rows and cols?"<<endl;
   // cout << "manual input: 1. read from file: 2." << endl;
    cout << "press 1 to start, followed by number of rows and columns to be generated." <<endl;
    cin >> answer;
    if(answer == 2){

        fout >> r >> c;
        //fout.close;
    }
    else{

        cin>>r>>c;
    }


    A = new double*[r];
    for(int i=0; i<r; i++){A[i]=new double[c];}
    b = new double[r];
    x = new double[r];

    //Gaussian(A,x,b,r);
    default_random_engine * gptr;
    gptr = new default_random_engine(time(NULL));
    normal_distribution<double> valdist(0.0, 50);
    uniform_real_distribution<double> xdist(10.0, 50.0);
    double val;
    double sum=0;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
           /// val = valdist(*gptr);
           val = 1.0;
            sum = sum + fabs(val);
            A[i][j]=val;
        }
        A[i][i]=sum;
        sum = 0.0;
        //val = xdist(*gptr);
        val = 1;
        x[i]= val;
    }

    cout<<"matrix A:"<<endl;
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;


    cout<<"solution x"<<endl;
    for(int i=0; i<r; i++)
    {
        cout<<x[i]<<endl;
    }
        MatVec(r,c,A,x,b);
    cout<<endl<<endl;


    cout<<"right side vector b"<<endl;
    for(int i=0; i<r; i++)
    {
        cout<<b[i]<<endl << endl;
    }
    Gaussian(A,x,b,r);
    return 0;
}

void MatVec(int r, int c, double **A, double*x, double* b)
{   double sum = 0;

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
             sum= sum + (A[i][j]*x[j]);
        }
        b[i]=sum;
        sum = 0.0;
    }
}
void Gaussian(double **A, double *x, double *b, int N){
    cout <<"Starting Gaussian Elimination." <<endl;

      double maxvalue;
      int maxrow;
      double temp;

      ShowMat(A,N,N);
//      ShowVec(A,N,N);
      for(int column = 0; column<N; column++)
        {

        maxrow = column;
        maxvalue = A[column][column];
        for(int row = column+1; row<N; row++)  // check for max row then swap
            {

            if(A[row][column]>maxvalue)
            {
                maxrow = row;
                maxvalue = A[row][column];
            }
        }

      if(maxrow != column)
      {
          for(int c = 0; c<N; c++)
          {
              temp = A[column][c];
              A[column][c]=A[maxrow][c];
              A[maxrow][c]=temp;
          }
          temp =b[column];                       //swap rows
          b[column]=b[maxrow];
          b[maxrow]=temp;
      }
            ShowMat(A,N,N);
      for(int c=0; c<N; c++)                            //divide all rows by max
      {
          A[column][c]=A[column][c]/maxvalue;
      }
      b[column]=b[column]/maxvalue;
            ShowMat(A,N,N);
      temp = A[column][column];
      for(int r = column + 1; r<N; r++)
      {
          temp = A[r][column];
          for(int d = 0; d<N; d++)
          {
              A[r][d] = A[r][d] - (A[column][d]*temp);
          }
          b[r] = b[r] - temp * b[column];
      }

      double sum;                             //here's the backsolve
      x[N-1]=b[N-1];
      for(int r = N-2; r>=0; r--)
      {
          sum = 0;
          for(int c = r+1; c < N; c++){

            sum = sum + A[r][c]*x[c];
            cout << "row " << r << " col " << c << " sum = " << sum <<endl;
          }
          x[r]= b[r]-sum;
          cout << "x{" <<r << "} =" <<x[r]<<endl;
      }

      cout <<"X" << endl;

      double * error = new double[N];
      double * bpredicted = new double[N];
//      MatVec(A,x,bpred,N);
      sum = 0.0;
      for(int i = 0; i<N; i++){

        error[i] = b[i] - bpredicted[i];
        sum = sum + pow(error[i],2);
      }

      double Two_norm = sqrt(sum);
      double AVG_ERROR = Two_norm/N;
      cout << "Two Norm: " << Two_norm << endl << "Average Error: " << AVG_ERROR << endl;
}


}
void ShowMat(double **A, int n, int m)
 {
     for(int i=0; i<n; i++)
        {for(int j=0; j<m; j++)
            {cout<<A[i][j]<<" ";}
        cout<<endl;
        }
    cout<<endl;
 }
 void ShowVec(double *V, int n)
     {for(int j=0; j<n; j++)
            {cout<<V[j]<<" ";}
        cout<<endl<<endl;
     }

