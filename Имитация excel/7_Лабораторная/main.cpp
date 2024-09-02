#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int N;
    int Summa1, Summa2;
    double *Lambda, *Mu1, *Mu2, *T1, *T2, *Lambda_Mu1;
    cout << "Введите количество элементов: ";
    cin >> N;
    cout << endl;
    Lambda = (double*)malloc(N * sizeof(double));
    Mu1 = (double*)malloc(N * sizeof(double));
    Mu2 = (double*)malloc(N * sizeof(double));
    T1 = (double*)malloc(N * sizeof(double));
    T2 = (double*)malloc(N * sizeof(double));
    Lambda_Mu1 = (double*)malloc(N * sizeof(double));

    for (int i=0; i<N; i++)
    {
        cout << "Введите значение Lambda: ";
        cin >> Lambda[i];
        cout << endl;

        cout << "Введите значение Mu1: ";
        cin >> Mu1[i];
        cout << endl;

        cout << "Введите значение Mu2: ";
        cin >> Mu2[i];
        cout << endl;
    }

    for (int i=0; i<N; i++)
    {
        if (Lambda[i] >= Mu1[i])
        {
            T1[i] = 1;
        }
        else
        {
            T1[i] = Lambda[i] / Mu1[i];
        }
    }

    for (int i=0; i<N; i++)
    {
        Lambda_Mu1[i] = Lambda[i] - Mu1[i];
    }

    for (int i=0; i<N; i++)
    {
        if (Lambda_Mu1[i] >= Mu2[i])
        {
            T2[i] = 1;
        }
        if (Lambda_Mu1[i] >= Mu2[i])
        {
            T2[i] = 0;
        }
        else
        {
            T2[i] = Lambda_Mu1[i] / Mu2[i];
        }
    }

    for (int i=0; i<N; i++)
    {
        Summa1 += T1[i];
        Summa2 += T2[i];
    }

    for (int i=0; i<N; i++)
    {
        cout << "Lambda[" << i+1 << "] = " << Lambda[i] << "   " << "Mu1[" << i+1 << "] = " << Mu1[i] << "   " << "Mu2[" << i+1 << "] = " << Mu2[i] << "   " << "T1[" << i+1 << "] = " << T1[i] << "   " << "T2[" << i+1 << "] = " << T2[i] << "   " << "Lambda-Mu1[" << i+1 << "] = " << Lambda_Mu1[i] << "   ";
        cout << endl;
    }

    double Sum1_Del_N = Summa1 / N;
    double Sum2_Del_N = Summa2 / N;

    cout << Sum1_Del_N << endl;
    cout << Sum2_Del_N << endl;

    free(Lambda);
    free(Mu1);
    free(Mu2);
    free(T1);
    free(T2);
    free(Lambda_Mu1);
    return 0;
}