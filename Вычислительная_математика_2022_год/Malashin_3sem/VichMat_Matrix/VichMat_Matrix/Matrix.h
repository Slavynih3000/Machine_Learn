#pragma once
#include <iostream>

class Matrix {
private:
	double** arr_a;
	double* arr_b;
	double* arr_x;

	int row;
	int col;

	void GetA() {
		std::cout << "Fill matrix A: " << std::endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				std::cin >> arr_a[i][j];
			}
		}
	}
	void GetB() {
		std::cout << "Fill matrix B: " << std::endl;
		for (int i = 0; i < row; i++) {
			std::cin >> arr_b[i];
		}
	}

	double get_spec_Det(double** matrix) {
		return matrixDet(matrix, col);
	}

	//Возвращает матрицу matrix без row-ой строки и col-того столбца, результат в newMatrix
	void getMatrixWithoutRowAndCol(double** matrix, int size, int row, int col, double** newMatrix) {
		int offsetRow = 0; //Смещение индекса строки в матрице
		int offsetCol = 0; //Смещение индекса столбца в матрице
		for (int i = 0; i < size - 1; i++) {
			//Пропустить row-ую строку
			if (i == row) {
				offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
			}

			offsetCol = 0; //Обнулить смещение столбца
			for (int j = 0; j < size - 1; j++) {
				//Пропустить col-ый столбец
				if (j == col) {
					offsetCol = 1; //Встретили нужный столбец, проускаем его смещением
				}

				newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
			}
		}
	}

	//Вычисление определителя матрицы разложение по первой строке
	double matrixDet(double** matrix, int size) {
		double det = 0;
		int degree = 1; // (-1)^(1+j) из формулы определителя

		//Условие выхода из рекурсии
		if (size == 1) {
			return matrix[0][0];
		}
		//Условие выхода из рекурсии
		else if (size == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else {
			//Матрица без строки и столбца
			double** newMatrix = new double* [size - 1];
			for (int i = 0; i < size - 1; i++) {
				newMatrix[i] = new double[size - 1];
			}

			//Раскладываем по 0-ой строке, цикл бежит по столбцам
			for (int j = 0; j < size; j++) {
				//Удалить из матрицы i-ю строку и j-ый столбец
				//Результат в newMatrix
				getMatrixWithoutRowAndCol(matrix, size, 0, j, newMatrix);

				//Рекурсивный вызов
				//По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть сумма из формулы)
				//где minor_j - дополнительный минор элемента matrix[0][j]
				// (напомню, что минор это определитель матрицы без 0-ой строки и j-го столбца)
				det = det + (degree * matrix[0][j] * matrixDet(newMatrix, size - 1));
				//"Накручиваем" степень множителя
				degree = -degree;
			}

			//Чистим память на каждом шаге рекурсии(важно!)
			for (int i = 0; i < size - 1; i++) {
				delete[] newMatrix[i];
			}
			delete[] newMatrix;
		}

		return det;
	}

	double Norma(double* arr) {
		double norma = 0;
		for (int i = 0; i < row; i++) {
			norma += abs(arr[i]);
		}

		return norma;
	}

public:
	Matrix() {
		std::cout << "Enter size of matrix: " << std::endl;
		std::cin >> row >> col;//Вводим размеры
		//Выделяем память под массивы
		arr_a = new double* [row];
		for (int i = 0; i < row; i++) {
			arr_a[i] = new double[col];
		}
		arr_b = new double[row];
		arr_x = new double[col];

		GetA();
		GetB();
	}

	double getDeterminant() {
		return matrixDet(arr_a, col);
	}

	void Kramer() {
		double** tmp_arr;
		tmp_arr = new double* [row];
		for (int i = 0; i < row; i++) {
			tmp_arr[i] = new double[col];
		}
		double main_det = getDeterminant();
		double tmp_det = 0;
		int counter = 0;
		while (counter != col) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					tmp_arr[i][j] = arr_a[i][j];
				}
			}
			for (int i = 0; i < col; i++) {
				tmp_arr[i][counter] = arr_b[i];
			}
			tmp_det = get_spec_Det(tmp_arr);
			std::cout << tmp_det << std::endl;
			arr_x[counter] = tmp_det / main_det;
			counter++;
		}

		for (int i = 0; i < col; i++) {
			std::cout << arr_x[i] << std::endl;
		}
	}

	void iter()
	{

		double** E;
		E = new double* [row];
		for (int i = 0; i < row; i++) {
			E[i] = new double[col];
		}
		double** A;
		A = new double* [row];
		for (int i = 0; i < row; i++) {
			A[i] = new double[col];
		}
		double* main_koef;
		main_koef = new double[row];
		double* B;
		B = new double[row];

		//Заполнение единичной матрицы
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == j)
					E[i][j] = 1;
				else
					E[i][j] = 0;
			}
		}

		for (int i = 0; i < row; i++) {
			main_koef[i] = arr_a[i][i];
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				A[i][j] = arr_a[i][j] / main_koef[i];
			}
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				A[i][j] = E[i][j] - A[i][j];
			}
		}
		
		for (int i = 0; i < row; i++) {
			B[i] = arr_b[i] / main_koef[i];
		}

		double* x_prev;
		double* x_next;
		x_prev = new double[row];
		x_next = new double[row];
		for (int i = 0; i < row; i++) {
			x_prev[i] = 1;
			x_next[i] = 0;
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				x_next[i] += A[i][j]*x_prev[j];
			}
			x_next[i] += B[i];
		}
		int counter = 0;
		while (counter < 1000) { //abs(Norma(x_next) - abs(Norma(x_prev))) >= 0.0001
			double* tmp_x;
			tmp_x = new double[row];
			for (int i = 0; i < row; i++) {
				tmp_x[i] = x_next[i];
			}

			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					x_next[i] += A[i][j] * x_prev[j];
				}
				x_next[i] += B[i];
			}

			for (int i = 0; i < row; i++) {
				x_prev[i] = tmp_x[i];
			}
			counter++;
		}

		for (int i = 0; i < row; i++) {
			std::cout << "x" << i << "= " << x_next[i] << std::endl;
		}
	}
};