#include <iostream>
#include <cmath>
using namespace std;

long double fact(int N)
{
    if(N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

long double ch(long double x, long double E = 0.000001)
{
    long double res = 0, last_elem, elem = 1.0;
    long double n = 1;
    do
    {
        res += elem;
        last_elem = elem;
        //elem += ((pow(x, n))/(fact(n)));
        elem = elem * x * x / (2 * n + 1) / (2 * n - 1);
        n++;
    } while (abs(elem - last_elem) > E);
    return res;
}

int main()
{
    long double result;
    result = ch(180);
    cout << result << endl;

    return 0;
}