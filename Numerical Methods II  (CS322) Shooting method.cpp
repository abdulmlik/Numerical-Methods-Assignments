/*
/////////// ********************************************************************************************* \\\\\\\\\\\
|                     This program                                                                                  |
|                     Solving Boundary Value Problem by Shooting method                                             |
|                                                                                                                   |
|                                         Written by Abdulmalik Ben Ali              start: 5/1/2107 end : 10/1/2018|
\\\\\\\\\\\ ********************************************************************************************* ///////////
*/
#include <iostream>//cout , cin
#include <iomanip>//setw
#include <limits> //numeric_limits<streamsize>::max()

using namespace std;

/*----- start Global Variable ---------*/

typedef float type;

/*------ End Global Variable----------*/
class shooting_method{
    type x1,x2,y1,y2,h;
    bool flage;
    type F(type X,type Y,type U)
    {
        return U;
    }
    type G(type X,type Y,type U)//U=Y`
    {
        return -(10*U+Y-1);
    }

    public:
        shooting_method()
        {
            flage = false;
        }
        shooting_method(type _x1, type _x2, type _y1, type _y2, type _h)
        {
            x1 = _x1;
            x2 = _x2;
            y1 = _y1;
            y2 = _y2;
            h  = _h;
            flage = true;
        }
        void setValue(type _x1, type _x2, type _y1, type _y2, type _h)
        {
            x1 = _x1;
            x2 = _x2;
            y1 = _y1;
            y2 = _y2;
            h  = _h;
            flage = true;
        }
        void shooting()
        {
            if(!flage) return;
            type u,sy1,sy2,su1,su2,temp1,temp2,c[2],d[2];
            temp1=x1;
            temp2=y1;
            int step;
            for(int i=0;i<2;i++)
            {

                if(i != 0)cout<<endl<<endl;
                cout<<"Enter U"<< i <<" ? ";
                cin>>u;
                d[i] = u;
                step = 1;
                while(x1 <= x2 - h)
                {
                    sy1 =  F(x1, y1, u);
                    su1 =  G(x1, y1, u);
                    sy2 =  F(x1 + h, y1 + h * sy1, u + h * su1);
                    su2 =  G(x1 + h, y1 + h * sy1, u + h * su1);
                    y1  += h * (sy1 + sy2) / 2;
                    u   += h * (su1 + su2) / 2;
                    x1  += h;
                    cout<<endl<<left<<setprecision(4) <<"X"
                    << step <<" : "<<setw(10)<<x1<<"  Y"<< step <<" : "<<setw(10)<<y1<<"   U"<< step << " : "<<setw(10)<<u;
                    step++;
                }
                c[i] = y1;
                x1 = temp1;
                y1 = temp2;
            }


                //for(i=0;i<2;i++)
                //cout<<endl<<d[i]<<"   "<<c[i];
            u = (y2-c[0])*(d[1]-d[0])/(c[1]-c[0])+d[0];
            cout<< endl <<  endl <<"Y`(0) : " << u <<endl;
            step = 0;
            while(x1 <= x2)
            {
                cout<<endl<<left <<setprecision(4) <<"X"<< step <<" : "<<setw(10)<<x1<<"  Y"<< step <<" : "<<setw(10)<<y1<<"   U"<< step << " : "<<setw(10)<<u;
                sy1 =  F(x1, y1, u);
                su1 =  G(x1, y1, u);
                sy2 =  F(x1 + h, y1 + h * sy1, u + h * su1);
                su2 =  G(x1 + h , y1 + h * sy1 , u + h * su1);
                y1  += h * (sy1 + sy2) / 2;
                u   += h*(su1 + su2) / 2;
                x1  += h;
                step++;
            }
            cout << endl;
        }
};

/*-----start function---------*/
void welcome();
void printScreens();        // طباعة الاختيارات على الشاشة

/*------End function----------*/

int main()
{
    char input;
    type x1,x2,y1,y2,h;
    do{
        system("cls");   // يمسح الكتابة في الشاشة السوداء
        welcome();
        printScreens();
        cout<<"\n\nEnter number \'1-2\' : ";    // اختيار رقم
        cin>>input;
        /*-------------  تجاهل جميع الاحرف او الارقام الزائدة عند الادخال --------------*/
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        /*------------------------------*/
        switch(input)
        {
            case '1':
            {
                cout<<"Enter x1,y1,x2,y2 ? ";
                cin>>x1>>y1>>x2>>y2;
                cout<<"Enter h ? ";
                cin>>h;
                shooting_method* x = new shooting_method(x1,x2,y1,y2,h);
                cout<<endl << "///------------------------///" << endl;
                x->shooting();
                cout<<endl << "///------------------------///" << endl;
                system("PAUSE");//يوقف التنفيذ
                break;
            }// end case
            case '2': return 0;
        }// end switch
    }while(1);
    return 0;
}//end main

void welcome()
{
	cout<<"                       ><><><><><><><><><><><><><\n"
	 <<"                     ><                          ><\n "
	 <<"                  ><     Date : 10.01.2018        ><\n"
	 <<"                 ><       Name : Abdulmalik Ben Ali ><\n"
	 <<"                 ><         ID : 213010551          ><\n"
	 <<"                   ><  Project : Numerical II     ><\n   "
	 <<"                  ><                          ><\n       "
	 <<"                ><><><><><><><><><><><><><\n\n";
}

void printScreens()
{
    cout << "\n\t\t1- Solving Boundary Value Problem by Shooting method." << endl;
    cout << "\n\t\t2- End Program." << endl;
}

