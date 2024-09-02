#include <iostream>
using namespace std;
const auto E = 0.000001;

double f(double x, double y)
{
    return -x * y * 2;
}

int main()
{
    double y0;
    cout << "Input y0: ";
    cin >> y0;
    cout << endl;

    double a, b;
    cout << "Input a and b: ";
    cin >> a >> b;
    cout << endl;
    int n;
    cout << "Input n: ";
    cin >> n;
    cout << endl;
    double d = (b - a) / n;

    double y_next = y0, y_previous = y0, x = a;
    for (int i = 0; i < n; i++)
    {
        y_previous = y_next;
        y_next = y_previous + d * f(x, y_previous);
        cout << x << "111 " << y_next << endl;
        x += d;
    }
    cout << y_next << endl;

    y_next = y0, y_previous = y0, x = a;
    double y, k1, k2, k3, k4;
    for (int i = 0; i < n; i++)
    {
        y_previous = y_next;
        k1 = d * f(x, y_previous);
        k2 = d * f(x + d / 2, y_previous + k1 / 2);
        k3 = d * f(x + d / 2, y_previous + k2 / 2);
        k4 = d * f(x + d, y_previous + k3);
        y = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        y_next = y_previous + y;
        cout << x << " " << y_next << endl;
        x += d;
    }
    cout << y_next << endl;



}

