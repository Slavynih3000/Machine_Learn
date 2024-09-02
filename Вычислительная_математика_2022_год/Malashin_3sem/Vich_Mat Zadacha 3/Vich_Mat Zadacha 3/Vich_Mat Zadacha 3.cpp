#include <iostream>

using namespace std;

const double E = 0.000001;

double Y(double x) {
	//X^3 + 4*X - 3 = 0
	return (pow(x, 3) + 4 * x - 3);
}

double Y1(double x) {
	//3*X^2 + 4
	return (3*x*x + 4); //Первая производная
}

double Y2(double x) {
	//6*X
	return (6 * x); //Вторая производная
}


void Polovin_Del(double A, double B) {
	double X = 0;
	int counter = 0;
	while (abs(A - B) >= 2 * E) {
		X = (A + B) / 2;
		if (Y(A) * Y(X) < 0)
			B = X;
		else
			A = X;
		counter++;
	}

	cout << "The root is: " << X << endl;
	cout << "The amount of iterations is: " << counter << endl;
}

void Newton(double A, double B) {
	double Xn = 0;
	int counter = 0;
	if (Y(A) < Y(B)) {
		Xn = B;
	}
	else {
		Xn = A;
	}

	while ((Y(Xn) / Y1(Xn)) > E) {
		Xn = Xn - Y(Xn) / Y1(Xn);
		counter++;
	}

	cout << "The root is: " << Xn << endl;
	cout << "The amount of iterations is: " << counter << endl;
}

int main() {
	//X^3 + 4*X - 3 = 0
	double x = 0;

	double prev = Y(x), next = Y2(x);
	while (prev * next < 0) {
		x++;
		prev = Y(x);
		next = Y2(x);
	}
	double B = x + 1;	//Правая граница
	double A = x;	//Левая граница

	Polovin_Del(A, B);
	Newton(A, B);
}