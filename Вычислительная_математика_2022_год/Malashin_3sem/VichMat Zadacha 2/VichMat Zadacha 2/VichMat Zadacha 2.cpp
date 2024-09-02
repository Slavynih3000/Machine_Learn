#include <iostream>
#include "Matrix.h"

int main() {
	Matrix m;
	//m.GetMatrixA();
	//m.GetMatrixB();
	m.PrintMatrixA();
	m.PrintMatrixB();
	std::cout << m.REZ() << std::endl;
}