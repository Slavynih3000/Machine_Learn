#include <iostream>//почитать методичку 6kf,
#include <cmath>//8. Нахождение значения определённого интеграла (3 способа)
using namespace std;
double s;
double f(double x)
{
    return (atan(x) + cos(x) - 1);
}

double trapeciy(double a, double b, int n)
{
    double h = (b-a)/n;
    double sum = f(a)+f(b);
    for (int i=0; i<n-1; i++)
    {
        sum += 2*f(a+i*h);
    }
    sum *= h/2;
    return sum;
}

double sympson(double a, double b, int n)
{
    double h = (b-a)/n;
    double sum = f(a)+f(b);
    int k;
    for (int i=0; i<n-1; i++)
    {
        k = 2+2*(i%2);
        sum += k*f(a+i*h);
    }
    sum *= h/3;
    return sum;
}

typedef double(*pointFunc)(double);

double trapeciy_integral(pointFunc f, double a, double b, int n)
{
    const double h = (b-a)/n;
    double k = 0;
    for (int i=1; i<n-1; i+=1)
    {
        k += f(a + (i+1)*h);
    }
    return h/2*(f(a) + 2*k);
}

double simpson_integral(pointFunc f, double a, double b, int n)
{
    const double h = (b-a)/n;
    double k1 = 0, k2 = 0;
    for(int i = 1; i < n; i += 2)
    {
        k1 += f(a + i*h);
        k2 += f(a + (i+1)*h);
    }
    return h/3*(f(a) + 4*k1 + 2*k2);
}

int main()
{
    double a, b;
    int n;
    a = 1;
    b = 2;
    n = 1000000;
    cout << "method trapezii = " << trapeciy(a, b, n) << endl;
    cout << "Method Simpsona = " << sympson(a, b, n) << endl;

    int i;
    double Integral; // интеграл
    double h = 0.0001;
    n = (double)((b - a) / h); // задаём число разбиений n (от этого зависит точность приближения)

    Integral = h * (f(a) + f(b)) / 2.0;
    for(i = 1; i <= n-1; i++)
    {
        Integral = Integral + h * f(a + h * i);
    }
    cout << "Po Method Trapezii = " << Integral << endl;

    Integral = h * (f(a) + f(b)) / 6.0;
    for(i = 1; i <= n; i++)
    {
        Integral = Integral + 4.0 / 6.0 * h * f(a + h * (i - 0.5));
    }
    for(i = 1; i <= n-1; i++)
    {
        Integral = Integral + 2.0 / 6.0 * h * f(a + h * i);
    }
    cout << "Po formula Simpsona = " << Integral << endl;

    double s1;
    
    s1 = trapeciy_integral(f, a, b, n);
    while (fabs(s1 - s) > h)
    {
        s = s1;
        n = 2*n;
        s1 = trapeciy_integral(f, a, b, n);
    }
    cout << "Trapecii = " << s1 << endl;

    s1 = simpson_integral(f, a, b, n); 
    while (fabs(s1 - s) > h)
    {
        s = s1;     //последующее приближение
        n = 2 * n;  //уменьшение значения шага в два раза
        s1 = simpson_integral(f, a, b, n);
    }
    cout << "Simpson = " << s1 << endl;

    return 0;
    getchar();
}
