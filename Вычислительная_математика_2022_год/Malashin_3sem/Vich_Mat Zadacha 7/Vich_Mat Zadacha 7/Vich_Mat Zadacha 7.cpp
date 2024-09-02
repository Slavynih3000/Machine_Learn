#include <iostream>
#include <random>
#include <iomanip>

using namespace std;

std::mt19937 mrand(std::time(0));
long unsigned int poisson(long unsigned int lambda)
{
	std::poisson_distribution<long unsigned int> d(lambda);
	return d(mrand);
}

long double fact(int N)
{
	if (N < 0)
		return 0;
	if (N == 0)
		return 1;
	else
		return N * fact(N - 1);
}

int main() {
	int amount;
	cout << "Enter amount of events: " << endl;
	cin >> amount;
	double** arr = new double* [amount];
	for (int i = 0; i < amount; i++) {
		arr[i] = new double[6];
	}

	srand(time(NULL));
	random_device rd;
	default_random_engine eng(rd());
	poisson_distribution<int> events(20);
	poisson_distribution<int> person(10);

	for (int i = 0; i < amount; i++) {
		bool flag = true;
		int lambda = 0;
		int m = 0;
		int n = 0;
		while (flag) {//Цикл, в котором рандомятся события и мощность обработчиков
			lambda = events(eng);
			m = person(eng);
			n = person(eng);

			if (lambda / (m * n) < 1)
				break;
		}
		if (i == 0) {
			arr[i][0] = lambda;
		}
		else {
			arr[i][0] = lambda + arr[i - 1][5];
		}
		arr[i][1] = m;
		arr[i][2] = n;

		if (arr[i][0] >= m) { //arr[i][]
			arr[i][3] = 1;
			if (((arr[i][0] - m) / n) > 1) {
				arr[i][4] = 1;
				arr[i][5] = arr[i][0] - m - n;
			}
			else {
				arr[i][4] = (arr[i][0] - m) / n;
				arr[i][5] = 0;
			}
		}
		else {
			arr[i][3] = lambda / m;
			arr[i][4] = 0;
			arr[i][5] = 0;
		}
	}

	for (int i = 0; i < amount; i++) {
		for (int j = 0; j < 6; j++) {
			cout << fixed << setprecision(2) << arr[i][j] << "\t";
		}
		cout << endl;
	}

	double T1 = 0;
	double T2 = 0;
	double ochered_med = 0;
	double lamda = 0;
	double m = 0;
	double n = 0;
	for (int i = 0; i < amount; i++) {
		ochered_med += arr[i][5];
		T2 += arr[i][4];
		T1 += arr[i][3] - arr[i][4];
		lamda += arr[i][0];
		m += arr[i][1];
		n += arr[i][2];
	}

	cout << "Srednyaya ochered: " << ochered_med/amount << endl;
	cout << "T1: " << T1 << endl;
	cout << "T2: " << T2 << endl;
	cout << "T0: " << amount - T1 - T2 << endl;
	cout << "P1: " << T1 / amount << endl;
	cout << "P2: " << T2 / amount << endl;
	cout << "P0: " << (amount - T1 - T2) / amount << endl;

	double p = 2;
	double p0 = 1;
	long int f = 1;
	int num = 2;
	for (int i = 0; i < num; i++)
	{
		p0 += (pow(p, i) / fact(i));
	}
	p0 += pow(p, 3) / ((n - p) * fact(n));
	p0 = 1 / p0;
	cout << endl << "P0 = " << p0 << " P1 = " << p * p0 << " P2 = " << p * p * p0 / 2;
}