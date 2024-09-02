#include "Matrix.h"

Matrix::Matrix() {
	strok = 0;
	stolb = 0;
	size = 3;
	GetMatrixA();
	GetMatrixB();
}
Matrix::Matrix(std::vector<std::vector<double>> a_ar, std::vector<double> b_ar) {
	a = a_ar;
	b = b_ar;
	strok = a_ar.size();
	stolb = a_ar[0].size();
}
Matrix::Matrix(const Matrix& copied) {
	a = copied.a;
	b = copied.b;
	strok = copied.strok;
	stolb = copied.stolb;
}
Matrix::Matrix(Matrix&& moved) noexcept{
	a = moved.a;
	b = moved.b;
	strok = moved.strok;
	stolb = moved.stolb;
}