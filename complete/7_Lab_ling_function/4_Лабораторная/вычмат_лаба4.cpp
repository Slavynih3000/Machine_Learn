#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;
#define e 1e-6
float mpd(float x) // functions mpd - "metod polovinnogo deleniya"
{
    return (3*cos(2*x+4));
    //return (sin(M_PI*x / 180) - 1 / x);
}

double find(double x, double eps)
{
    double f, df;
    int iter = 0;
    cout << "x0= " << x << " ";

    do
    {
        //f = sin(M_PI*x / 180) - 1 / x;
        //df = M_PI / 180 * cos(M_PI*x / 180) + 1 / (x*x);
        f = 3*cos(2*x+4);
        df = (-6*sin(2*x+4));
        x = x - f / df;
        iter++;
    } while (fabs(f) > eps && iter<20000);
    cout << iter << " iterations" << endl;
    return x;
}

int main()
{
    setlocale(0, "");
    float a,b,e,x; int k=0;
    cout<<"1. y=3*cos(2*x+4)\n";
    //cout << "y=sin(M_PI*x / 180) - 1 / x";
    cout<<"Левая граница a=";
    cin>>a;
    cout<<"Правая граница b=";
    cin>>b;
    /*cout<<"Точность e=";
    cin>>e;*/
    x=(a+b)/2;
    //cout<<"Корень уравнения:"<<x;

    while(fabs(b-a)>e)
    {
        if(mpd(a)*mpd(x)<=0)
            b=x;
        else
            a=x;
        x=(a+b)/2;
        k++;
        cout<<"\nТочность: "<<fabs(b-a)<<" Итерация №="<<k<<" Корень уравнения: "<<x;
    }
    cout<<"\nКоличество итераций ="<<k<<"\nКорень уравнения: "<<x;

    cout << find(1, 0.00001);

    return 0;
}