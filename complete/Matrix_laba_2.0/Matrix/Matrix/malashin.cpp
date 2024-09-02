#include <iostream>
#include <fstream>
#include <time.h>
#include <omp.h>
#include <vector>

using namespace std;

bool converge(double* xk, double* xkp, int n, double eps);

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    int i, j, n, m;
    char d;
    float** matrix = NULL;
    double* xx = NULL;
kt:
    i = 0, j = 0, n = 0, m = 0;
    cout << "1 - метод Гаусса ";
    cout << endl;
    cout << "2 - метод Зейделя ";
    cout << endl;
    cout << "4 - выход ";
    cout << endl;
    cout << "введите: ";
    cin >> d;
    cout << endl;
    if (d > '4' || d < '1') {
        cout << "правильно выберите пункт меню и введите число ";
        cout << endl;
        goto kt;
    }

    if (d == '4') { return 0; }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    cout << "Количество уравнений: ";
    cin >> n;//
    m = n + 1;

    matrix = new float* [n];
    for (int i = 0; i < n; i++) { matrix[i] = new float[m]; }

    ifstream Infile;
    Infile.open("mass.txt");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Infile >> matrix[i][j];
    Infile.close();   

    cout << "расширенная матрица" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    
    cout << endl;
    cout << endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (d == '1') {
        xx = new double[m];
        float  tmp;
        int k;
        for (i = 0; i < n; i++) {
            tmp = matrix[i][i];
            for (j = n; j >= i; j--) {
                float vb = matrix[i][j];
                matrix[i][j] = matrix[i][j] / tmp;
            }
            for (j = i + 1; j < n; j++) {
                tmp = matrix[j][i];
                for (k = n; k >= i; k--) {
                    float vb = matrix[j][k];
                    matrix[j][k] = matrix[j][k] - tmp * matrix[i][k];
                }
            }
        }

        xx[n - 1] = matrix[n - 1][n];
        for (i = n - 2; i >= 0; i--) {
            xx[i] = matrix[i][n];
            for (j = i + 1; j < n; j++) xx[i] -= matrix[i][j] * xx[j];
        }

        cout << "решения системы уравнений" << endl;
        for (i = 0; i < n; i++)
            cout << xx[i] << " ";
        cout << endl;

        delete[] matrix;

        goto kt;
    }

    if (d == '2'){
        double eps = 1e-6;
        /*cout << "Точность вычисления: " << endl;
        cin >> eps;*/
        xx = new double[n];
        double* p = new double[n];

        int k = 1;
        double sum;
        for (int i = 0; i < n; i++) {//проверяем главную диагональ больше ли она чем элементы на той же строке
            sum = 0;
            for (int j = 0; j < n; j++) sum += abs(matrix[i][j]);
            sum -= abs(matrix[i][i]);
            if (sum > matrix[i][i]) {
                k = 0;
            }
        }

        if (k) {
            for (int i = 0; i < n; i++)
                xx[i] = 0;

            do{
                for (int i = 0; i < n; i++)
                    p[i] = xx[i];

                for (int i = 0; i < n; i++){
                    double var = 0;
                    for (int j = 0; j < n; j++)
                        if (j != i) var += (matrix[i][j] * xx[j]);

                    for (int k = 0; k <= m*n; k+=m) {
                        xx[i] = (matrix[i][n] - var) / matrix[i][i];
                    }
                    
                }
                m++;
            } while (!converge(xx, p, n, eps));



            cout << "Решение системы:" << endl << endl;
            for (i = 0; i < n; i++) cout << "x" << i << " = " << xx[i] << "" << endl;
            cout << "Итераций: " << m << endl;


        }
        else {
            cout << "Не выполняется преобладание диагоналей" << endl;
        }
    }
} 
    
bool converge(double* xk, double* xkp, int n, double eps) {
    double norm = 0;
    for (int i = 0; i < n; i++)
        norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
    return (sqrt(norm) < eps);
}

