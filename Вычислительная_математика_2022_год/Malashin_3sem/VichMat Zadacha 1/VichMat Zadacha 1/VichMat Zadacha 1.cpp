#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const double x0 = 0;
const double E = 0.000001;

double SIN(double X) {
    double XXX = X;
    int c = trunc(XXX / (2 * M_PI));
    XXX -= 2 * M_PI * c;
    //Циклы, вычитающие лишние круги
    if (X > 2 * M_PI) {
        while (X > 2 * M_PI) {
            X -= 2 * M_PI;
        }
    }
    else if (X < 2 * M_PI) {
        while (X > 2 * M_PI) {
            X += 2 * M_PI;
        }
    }
    cout << "X after rounding" << endl;
    cout << X << endl;
    cout << XXX << endl;

    double sum = 0; //Итоговая сумма
    double previous = 0;
    double next = X;
    int counter = 1;
    int fact = 1;
    double An = X / counter;

    while (abs(next - previous) > E) {
        switch (counter % 4) {
        case 0:
            previous = next;
            counter++;
            An *= X / counter;
            next = 0;
            break;
        case 1:
            previous = next;
            sum += An;
            counter++;
            An *= X / counter;
            next = An;
            break;
        case 2:
            previous = next;
            counter++;
            An *= X / counter;
            next = 0;
            break;
        case 3:
            previous = next;
            sum -= An;
            counter++;
            An *= X / counter;
            next = -An;
            break;
        default:
            break;
        }
    }
    return sum;
}

double E_power_x(double X) {
    double int_res = 1;
    double drob_res;
    int integer_part = trunc(X);
    double drob_part = X - integer_part;

    double previous = 0;
    double next = 1;
    int counter = 0;

    drob_res = 1;
    while (abs(next - previous) >= E) {
        counter++;
        previous = next;
        next *= drob_part / counter;
        drob_res += next;
    }
    
    cout << "Drobnaya chast:" << drob_res << endl;

    if (integer_part > 0) {
        for (int i = 0; i < integer_part; i++) {
            int_res *= M_E;
        }
    }
    else {
        for (int i = 0; i > integer_part; i--) {
            int_res *= 1 / M_E;
        }
    }
    double result = int_res * drob_res;

    return result;
}

int main()
{
    //      sin(x^2 - 8)/e^x
    cout << "Enter a number: " << endl;
    double number;
    cin >> number;

    double val1 = pow(number, 2) - 8;
    double val2 = number;

    long double result1 = SIN(val1);
    long double result2 = E_power_x(val2);

    cout << "SIN IS: " << result1 << endl;
    cout << "E^X IS: " << result2 << endl;
    cout << "The result is: " << result1 / result2 << endl;
}