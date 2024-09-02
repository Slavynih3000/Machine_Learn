#include <iostream>
#include <math.h>

using namespace std;
int a[21] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 37, 43, 47, 53, 59, 67, 73, 79, 83, 89, 97};

int main() {
    setlocale(LC_ALL, "Russian");

    long double x = 503;
    long double eps = 0.00000000000001;

    long double fact = 1, fact_tmp = 0, num = 1, \
        square = x, value = 1, value_tmp = 10, i = 1;
    
    int number_decomposition_members = 0; //количество членов разложения
    while (abs(value - value_tmp) > eps) {
        value_tmp = value;

        fact_tmp++; //факториал ряда
        fact *= fact_tmp;
        for (int l = 0; l < 21; l++) {
            if ((long int)(fact / a[l]) && (long int)((square) / a[l])) {
                fact = fact / a[l];
                square = square / a[l];
            }
        }
        /*for (int l = 0;l<21; l++) {
            if (fact / a[l] && (square*i) / a[l]) {
                value += (((square*i)/a[l]) / (fact / a[l]));
            }
            else value += (i * square / fact); 
        }*/
        value += (i*square / fact); //значение члена разложения
        cout << (long double)value - 1 << endl;
        

        square *= x; //квадрат радя 
        i++;
        number_decomposition_members++;
    }

    cout << "x*exp(x) = " << (long double)(x*exp(x)) << "\n";
    cout << "количество членов разложения = " << number_decomposition_members << "\n\n\n";
}
