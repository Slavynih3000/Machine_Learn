#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
#define n 100
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

static double rg(double t, double x)//метод Рунге-Кутты
{
    //return log(x)+1;
    return x/t-log(t)/t;
}
float eyler(float x, float y) // метод Эйлера
{
    return y/x-log(x)/x;
}
double func(double x, double y);
double func2(double x);
float ya(float x) // аналитическое решение
{
    return log(x)+1;
}
void progonka();

int main ()
{
    float a, b, h, x, y[n];
    int k;

    a=1; b=2; h=(b-a)/(n-1);
    y[0]=1; // начальное условие y[a]=

    for (k=1; k<n; k++) // метод Эйлера
    {
        x=a+k*h;
        y[k]=y[k-1]+h*eyler(x,y[k-1]);
    }

    for (k=0; k<n; k++)
    {
        x=a+k*h;
        cout << "X = " << x;
        cout << endl;
        cout << "Метод Эйлера = " << y[k];
        cout << endl;
        cout << "Аналитическое решение = " << ya(x);
        cout << endl;
    }
    cout << endl;

    double t = 1.0;
    double t_end = 1.1;

    double rg_y = 1.0;
    double rg_h = 0.025;

    cout << setprecision(16);

    int rg_n = static_cast<int>((t_end - t) / rg_h);

    for (int i = 0; i < n; i++)
    {
        double k1 = rg(t, rg_y);
        double k2 = rg(t + rg_h / 2.0, rg_y + rg_h*k1 / 2.0);
        double k3 = rg(t + rg_h / 2.0, rg_y + rg_h*k2 / 2.0);
        double k4 = rg(t + rg_h, rg_y + rg_h*k3);

        rg_y += ((k1 + 2 * k2 + 2 * k3 + k4) * rg_h / 6.0);

        cout << t << ": " << rg_y << endl;

        t += rg_h;
    }

    progonka();

    getchar();
}

double func(double x, double y)
{
    return x * x - 2 * y;
}

void progonka()
{
    double h = 0.1;
    /* y" + (x + 1)*y' - 2y = 2
     y(0) - y'(0) = -1
     y = (x + y) ^ 2*/
    double a = 0, b = 1;
    h = (b-a)/n;
    double B = 4;

    double ai = 1 - h/2, bi = h * h * (-2) - 2, ci = 1 + h/2, di = h * h * 2;
    double vi = -(ci / bi), ui = di / bi;

    vector<pair<double, double>> v;

    v.push_back(make_pair(ui, vi));

    for (double i = a; i <= b; i += h)
    {
        ai = 1 - h *(i + 1)/2;
        bi = h * h * (-2) - 2;
        ci = 1 + h * (i + 1)/2;
        di = h * h * 2;

        double prevvi = vi;
        vi = -ci / (bi + ai * vi);
        ui = (di - ai * ui)/ (bi + ai * prevvi);

        v.push_back(make_pair(ui, vi));
    }

    double yn = B;
    vector<double> v2;

    v2.push_back(yn);
    for (int i = v.size() - 1; i >= 1; i--) {
        yn = v[i].first + v[i].second * yn;
        v2.push_back(yn);
    }

    reverse(v2.begin(), v2.end());

    cout << "Sweep" << endl;
    printf("%-10s %-10s\n", "X", "Решение прогонкой");
    double j = a;
    for (int i = 0; i < v2.size(); i++, j += h)
    {
        printf("%-10f %-10f\n", j, v2[i]);
    }
}
