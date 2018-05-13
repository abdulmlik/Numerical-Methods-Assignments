/*
/////////// ********************************************************************************************* \\\\\\\\\\\
|                     This program                                                                                  |
|                     Solving Linear Equations by Gaussian Elimination & LU Decomposition                           |
|                     And Find a Determinant                                                                        |
|                                                                                                                   |
|                                         Written by Abdulmalik Ben Ali                                   22/5/2107 |
\\\\\\\\\\\ ********************************************************************************************* ///////////
*/
//Have g++ follow the C++14 ISO C++ language standard [-std=c++14]
#include <iostream>
#include <string>
#include <limits> //numeric_limits<streamsize>::max()
#include <iomanip>//setw
#include <cmath>

using namespace std;


/*----- start Global Variable ---------*/

typedef float type;//نوع المصفوفة لتغير نوع المصفوفة يغير من هنا فقط
type **Array = NULL ;// المصفوفة
int N;              // حجم المصفوفة
bool trun = false;  // هذا المتغير يرمز اذا تم تكوين المصفوفة او لا

/*------ End Global Variable----------*/

/*-----start function---------*/

void printScreens();        // طباعة الاختيارات على الشاشة
void createArray();         // تكوين مصفوفة واضافة العناصر
//-----
void gaussianElimination(); // طريقة الحذف لجاوس
void LUD();                 // طريقة التحليل
type  det();                 // حساب محدد المصفوفة
//------
void printArrar();                  //  طباعة المصفوفة
void printArrarOneDim(type*,int);    //1D طباعة مصفوفة
void printArrarTwoDim(type**,int,int,int);//2D طباعة مصفوفة

/*------End function----------*/

int main()
{
    char input;
    do{
        system("cls");  // يمسح الكتابة في الشاشة السوداء
        printScreens();
        cout<<"\n\nEnter number \'1-5\' : ";    // اختيار رقم
        cin>>input;
        /*------------- تجاهل جميع الاحرف او الارقام الزائدة عند الادخال --------------*/
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        /*------------------------------*/
        switch(input)
        {
            case '1':
            {
                createArray();
                system("PAUSE");//يوقف التنفيذ
                break;
            }// end case 1
            case '2':
            {
                if(trun)
                {
                    system("cls");
                    gaussianElimination();
                    cout << endl << endl;

                }
                else{
                    cout << endl << "The Array does not Exist Please Create The Array" << endl << endl;
                }
                system("PAUSE");
                break;
            }// end case 2
            case '3':
            {
                if(trun)
                {
                    system("cls");
                    printArrar();
                    cout << "Determinant : " << det() << endl << endl;
                }
                else{
                    cout << endl << "The Array does not Exist Please Create The Array" << endl << endl;
                }
                system("PAUSE");
                break;
            }//end case 3
            case '4':
            {
                if(trun)
                {
                    system("cls");
                    LUD();
                }
                else{
                    cout << endl << "The Array does not Exist Please Create The Array" << endl << endl;
                }
                cout << endl;
                system("PAUSE");
                break;
            }//end case 4
            case '5': return 0;
        }// end switch
    }while(1);
}//end main

void printScreens()
{
    cout << "\n\t\t\tName           : Abdulmalik Ben Ali" << "\n\t\t\tStudent Number : 213010551" << endl;
    cout << "\n\t\t1- Create Array and insert Number of Array ." << endl;
    cout << "\n\t\t2- Solving Linear Equations With Gaussian Elimination." << endl;
    cout << "\n\t\t3- Display The Determinant." << endl;
    cout << "\n\t\t4- Solving Linear Equations With LU Decomposition." << endl;
    cout << "\n\t\t5- End Program." << endl;
}

/* ----------   start Create Array  --------------- */
void createArray()
{
    if(trun)// يحذف المصفوفة اذا كانت موجودة
    {
        for( int i = 0 ; i < N ; i++ )
        {
            delete []Array[i];
        }
        delete []Array;
    }// end delete Array
    string s;
    do{
        system("cls");
        cout << "Enter No of equations : ";
        cin >> s;
        // string.find_first_not_of("") دالة ترجع مكان اول حرف في السلسلة غير موجود في النص المعطى
    }while( s.find_first_not_of( "0123456789" ) != string::npos );// يجب ان يدخل رقم
    N = stoi(s); // يحول من السلسلة الى رقم صحيح
    Array = new type*[N];
    for( int i = 0 ; i < N ; i++ )
    {
            Array[i] = new type[N+1];
    }
    for( int i = 0 ; i < N ; i++ )
    {
        cout << "Enter equations " << i << ":" << endl;
        for( int j = 0 ; j < N ; j++ )
        {
            cout << "A[" << i << "][" << j << "] = " ;
            cin >> Array[i][j];
        }
    }//end insert matrix A
    cout << "\nEnter matrix B :" << endl;
    for( int i = 0 ; i < N ; i++ )
    {
        cout << "B[" << i << "] = " ;
        cin >> Array[i][N];
    }
    trun = true;
}//end create array
/* ----------   end Create Array  --------------- */


/* ----------   start Gaussian Elimination  --------------- */

// دالة التبدييل بين صفين
void swapRow(type **matrix, int i, int j)
{
    //cout << "Swapped rows " << i << " and " << j << endl;
    type temp;
    for (int c = 0; c <= N; c++)
    {
        temp = matrix[i][c];
        matrix[i][c] = matrix[j][c];
        matrix[j][c] = temp;
    }
}

// دالة تقوم بحذف العناصر اسفل القطر الرئيسي
int fElim(type** matrix)
{
    type f;
    for (int k=0; k<N; k++)
    {
        /* --------- عملية الارتكاز ------------- */
        int indexMax = k;
        int valueMax = matrix[indexMax][k];

        for (int i = k+1; i < N; i++)
        {
            if (abs(matrix[i][k]) > abs(valueMax))
            {
                valueMax = matrix[i][k];
                indexMax = i;
            }
        }

        /* اذا ظهر صف اصفار */
        if (!matrix[k][indexMax])
        {
            return k;// يرجع رقم الصف
        }

        /* يبدل بين صفين */
        if (indexMax != k)
        {
            swapRow(matrix, k, indexMax);
        }
        /* -------------------- */

        /* عملية الاختزال */
        for (int i=k+1; i<N; i++)
        {
            f = matrix[i][k]/matrix[k][k];
            for (int j=k+1; j<=N; j++)
            {
                matrix[i][j] -= matrix[k][j]*f;
            }
            matrix[i][k] = 0;
        }
         /* ----------------------- */

        //printArrarTwoDim(matrix,N,N+1,1);        //print array step by step
    }
    printArrarTwoDim(matrix,N,N+1,1);            //print array end step
    return -1;
}

// دالة التعويض بالخلف
void BKSUB(type** matrix)
{
    type x[N];  // يخزن قيم فيه

    /* يبدا التعويض بالخلف */
    for (int i = N-1; i >= 0; i--)
    {
        /* يضع ناتج المعادلة */
        x[i] = matrix[i][N];

        for (int j=i+1; j<N; j++)
        {
            /* يحسب بقية القيم في المعادلة */
            x[i] -= matrix[i][j]*x[j];
        }

        /* يقسم ناتج المعادلة على معامل المعادلة */
        x[i] = x[i]/matrix[i][i];
    }

    cout << "\nSolution for the system:\n";
    for (int i=0; i<N; i++)
    { cout << "X" << i << " = " << x[i] << "\t"; }
}

void gaussianElimination()// طريقة الحذف لجاوس
{
    type **matrix = new type*[N];
    for( int i = 0 ; i < N ; i++ )
    {
        matrix[i] = new type[N+1];
    }
    for( int i = 0 ; i < N ; i++ )
    {
        for( int j = 0 ; j < N+1 ; j++)
        {
            matrix[i][j] = Array[i][j];
        }
    }
    int IFLAG = fElim(matrix);
     /* هل ظهر صف اصفار */
    if (IFLAG != -1)
    {
        cout << "Singular matrixrix.\n";

        /* عدد لانهائي من الحلول او لايوجد حل*/
        if (matrix[IFLAG][N])
        {
            cout << "Inconsistent System.";
        }
        else
        {
            cout << "May have infinitely many solutions.";
        }

        return;
    }

    /* تعويض بالخلف*/
    BKSUB(matrix);
    for( int i = 0 ; i < N ; i++ )
    {
        delete []matrix[i];
    }
    delete []matrix;
    matrix = NULL;
}//end gaussian Elimination

/* ----------   end Gaussian Elimination  --------------- */

/* ----------   start Determinant  --------------- */

type det()// دالة حساب المحدد
{
    type **temp, D = 1;
    temp = new type*[N];
    for(int i =0 ; i<N;i++)
    { temp[i] = new type[N+1]; }

    for(int i=0;i<N ;i++)
    {
        for(int j=0;j<=N ;j++)
        {
            temp[i][j] = Array[i][j];
        }
    }
    type f;
    for (int k=0; k<N; k++)
    {
        /* --------- عمليةالارتكاز ------------- */
        int indexMax = k;
        int valueMax = temp[indexMax][k];

        for (int i = k+1; i < N; i++)
        {
            if (abs(temp[i][k]) > abs(valueMax))
            {
                valueMax = temp[i][k];
                indexMax = i;
            }
        }

        /* استبدال صف */
        if (indexMax != k)
        {
            swapRow(temp, k, indexMax);
            D *= -1;// تغير اشارة المحدد عند استبدال صف
        }
        /* -------------------- */

        /* عملية الاختزال */
        for (int i=k+1; i<N; i++)
        {
            f = temp[i][k]/temp[k][k];
            for (int j=k+1; j<=N; j++)
            {
                temp[i][j] -= temp[k][j]*f;
            }
            temp[i][k] = 0;
        }

    }
    for( int i = 0 ; i < N ; i++)
    {
        D *= temp[i][i];
    }
    for( int i = 0 ; i < N ; i++ )
    {
        delete []temp[i];
    }
    delete []temp;
    temp = NULL;
    return D;
}

/* ----------   end Determinant  --------------- */

/* ----------   start LU Decomposition  --------------- */

void LUD()
{
    type    L[N+1][N+1]={0},
            U[N+1][N+1]={0},
            B[N+1]={0},
            B_[N+1]={0},
            X[N+1]={0},
            sum = 0;

    for(int i = 1 ; i <= N ; i++)
    {
        B[i] = Array[i-1][N];
    }

    //********** LU حيساب مصفوفة *****//
    for(int c = 1 ; c <= N ; c++)
    {
        U[c][c] = 1;
        for(int i = c ; i <= N ; i++)
        {
            sum = 0;
            for(int k = 1; k<= c-1; k++)
            {
                sum += L[i][k] * U[k][c];
            }
            L[i][c] = Array[i-1][c-1] - sum;
        }

        for(int j = c + 1 ; j <= N ; j++)
        {
            sum = 0;
            for(int k = 1 ; k <= c - 1 ; k++)
            {
                sum += L[c][k] * U[k][j];
            }
            U[c][j]=(Array[c-1][j-1] - sum) / L[c][c];
        }
    }

    cout << "Solution for L : " << endl;
    for(int i = 1 ; i <= N ; i++)
    {
        for(int j = 1 ; j <= N ; j++)
        {
            cout << setw(8) << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nSolution for U : " << endl;
    for(int i = 1 ; i <= N ; i++)
    {
        for(int j = 1 ; j <= N ; j++)
        {
            cout << setw(8) << U[i][j] << " ";
        }
        cout << endl;
    }
    //////////////////////end LU decomposition


    //***** B` حساب مصفوفة ; LB`=B *********//

    for(int i = 1 ; i <= N ; i++)
    {
        sum = 0;
        for(int j = 1 ; j<i ; j++)
            sum += L[i][j] * B_[j];
        B_[i] = ( B[i] - sum ) / L[i][i];
    }


    cout<< "\nSolution for B` :" << endl;
    for(int i=1 ; i<=N ;i++)
    {
        cout << "B`" << i << " = " << B_[i] <<"\t";
    }
    ////////////////////end B`

     //********** X حساب ; UX=B` ***********//

     for(int i = N ; i > 0 ; i--)
    {
        sum=0;
        for(int j = N ; j>i ;j--)
            sum+=U[i][j]*X[j];
        X[i]=(B_[i]-sum)/U[i][i];
    }
    cout << endl << "\nSolution for the system :" << endl;
    for(int i=1 ; i<=N ;i++)
    {
        cout << "X" << i << " = " << X[i] <<"\t";
    }
    /////////////////////////end X
}

/* ----------   end LU Decomposition  --------------- */

void printArrar()
{
    if( Array == NULL ) return;
    cout  << endl;
    for( int i = 0 ; i < N ; i++ )
    {
        for( int j = 0 ; j < N+1 ; j++ )
        {
            if( j == N ) cout << setw(4) << "| ";
            cout << setw(8) << Array[i][j];
            if( j != N ) cout << " ";
        }
        cout << endl;
    }
    cout  << endl;
}
void printArrarOneDim(type* A,int n)
{
    if( A == NULL ) return;
    cout << endl;
    for( int i = 0 ; i < n ; i++ )
    {
        cout <<  A[i];
        if( i != n-1 ) cout << " ";
    }
    cout  << endl;
}
void printArrarTwoDim(type** A,int n,int m, int y = 0)
{
    if( A == NULL ) return;
    cout  << endl;
    for( int i = 0 ; i < n ; i++)
    {
        for( int j = 0 ; j < m ; j++)
        {
            if( j == n  && y ) cout << setw(4) << "| ";
            cout << setw(8) <<  A[i][j];
            if( j != m-1 ) cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}
