#pragma once
#include <iostream>
#include <vector>

class Matrix {
private:
	std::vector<std::vector<double>> a;
	std::vector<double> b;
	int strok;
	int stolb;
	int size;
public:
	Matrix();
	Matrix(std::vector<std::vector<double>> a_ar, std::vector<double> b_ar);
	Matrix(const Matrix& copied);
	Matrix(Matrix&& moved) noexcept;

	void GetMatrixA() {
		std::cout << "Input koef for Xi: " << std::endl;
		std::vector<double> tmp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				int num;
				std::cin >> num;
				tmp.push_back(num);
			}
			a.push_back(tmp);
			tmp.clear();
		}
	}
	void GetMatrixB() {
		std::cout << "Input free koef: " << std::endl;
		for (int i = 0; i < 3; i++) {
			int num;
			std::cin >> num;
			b.push_back(num);
		}
	}
	void PrintMatrixA() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void PrintMatrixB() {
		for (int i = 0; i < 3; i++) {
			std::cout << b[i] << " ";
		}
		std::cout << std::endl;
	}


	double REZ() {
		double rez = Determ(a, size);
		return rez;
	}
	double Determ(std::vector<std::vector<double>> array, int size) {
		int determinant = 0;
		int phase = 1;

		if (size == 1) {
			return array[0][0];
		}
		else if (size == 2) {
			return array[0][0] * array[1][1] - array[0][1] * array[1][0];
		}
		else {
			std::vector<std::vector<double>> newMatrix;

			//������������ �� 0-�� ������, ���� ����� �� ��������
			for (int j = 0; j < size; j++) {
				//������� �� ������� i-� ������ � j-�� �������
				//��������� � newMatrix
				getMatrixWithoutRowAndCol(array, size, 0, j, newMatrix);

				//����������� �����
				//�� �������: ����� �� j, (-1)^(1+j) * matrix[0][j] * minor_j (��� � ���� ����� �� �������)
				//��� minor_j - �������������� ����� �������� matrix[0][j]
				// (�������, ��� ����� ��� ������������ ������� ��� 0-�� ������ � j-�� �������)
				determinant = determinant + (phase * array[0][j] * Determ(newMatrix, size - 1));
				//"�����������" ������� ���������
				phase = -phase;
			}

			//������ ������ �� ������ ���� ��������(�����!)
			//newMatrix.clear();
		}

		return determinant;
	}
	//���������� ������� matrix ��� row-�� ������ � col-���� �������, ��������� � newMatrix
	void getMatrixWithoutRowAndCol(std::vector<std::vector<double>> matrix, int size, int row, int col, std::vector<std::vector<double>> newMatrix) {
		int offsetRow = 0; //�������� ������� ������ � �������
		int offsetCol = 0; //�������� ������� ������� � �������
		for (int i = 0; i < size - 1; i++) {
			//���������� row-�� ������
			if (i == row) {
				offsetRow = 1; //��� ������ ��������� ������, ������� ���� ����������, ������ �������� ��� �������� �������
			}

			offsetCol = 0; //�������� �������� �������
			for (int j = 0; j < size - 1; j++) {
				//���������� col-�� �������
				if (j == col) {
					offsetCol = 1; //��������� ������ �������, ��������� ��� ���������
				}

				newMatrix[i][j] = matrix[i + offsetRow][j + offsetCol];
			}
		}
	}
};