#include <iostream>
#include <iomanip>

using namespace std;

constexpr double E = 0.0000001;

double fdx(double X) {
    return (sqrt(X * X + 1) + 4*X*X*X + 2);//f(x^4 + 2x)
    //return cos(X);
}

int main() {
    //sqrt(x^2+1) + x^4 + 2x
    double x_next = 1;
    double x_prev = 0;

    double alfa = 0.001;
    int counter = 0;
    while (abs(x_next - x_prev) >= E)
    {
        x_prev = x_next;
        x_next = x_next - alfa * fdx(x_next);
        counter++;
    }

    cout << fixed << setprecision(5) << x_next << " for " << counter << " iterations" << endl;;
}