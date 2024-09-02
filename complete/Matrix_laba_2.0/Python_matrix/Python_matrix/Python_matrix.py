#-*- coding: utf-8 -*-

class Matrix:
    def __init__(self, rows, cols, data=None):
        self.rows = rows
        self.cols = cols
        if data:
            self.data = data
        else:
            self.data = [[0] * cols for _ in range(rows)]

    def __getitem__(self, index):
        return self.data[index]

    def __setitem__(self, index, value):
        self.data[index] = value

    def __str__(self):
        return "\n".join([" ".join(map(str, row)) for row in self.data])

    def determinant(self):
        if self.rows != self.cols:
            raise ValueError("Matrix make be like rectangle")
        if self.rows == 1:
            return self.data[0][0]
        if self.rows == 2:
            return self.data[0][0] * self.data[1][1] - self.data[0][1] * self.data[1][0]

        det = 0
        for col in range(self.cols):
            det += ((-1) ** col) * self.data[0][col] * self.minor(0, col).determinant()
        return det

    def minor(self, row, col):
        minor_matrix = Matrix(self.rows - 1, self.cols - 1)
        for i in range(self.rows):
            for j in range(self.cols):
                if i != row and j != col:
                    minor_row = i - (1 if i > row else 0)
                    minor_col = j - (1 if j > col else 0)
                    minor_matrix[minor_row][minor_col] = self.data[i][j]
        return minor_matrix

    def solve_cramer(self, constants):
        if self.rows != self.cols:
            raise ValueError("Matrix make be like rectangle")
        if len(constants) != self.rows:
            raise ValueError("Count const make be equally equation")

        det_A = self.determinant()
        if det_A == 0:
            raise ValueError("Opredelitel raven 0 ne opredelimo")

        solutions = []
        for i in range(self.cols):
            matrix_A_i = self.copy()
            for j in range(self.rows):
                matrix_A_i[j][i] = constants[j]
            det_A_i = matrix_A_i.determinant()
            solutions.append(det_A_i / det_A)

        return solutions

    def solve_gauss(self, constants):
        augmented_matrix = Matrix(self.rows, self.cols + 1)
        for i in range(self.rows):
            augmented_matrix[i] = self.data[i] + [constants[i]]

        for i in range(self.rows):
            # Приведение к верхнетреугольному виду
            for j in range(i + 1, self.rows):
                factor = augmented_matrix[j][i] / augmented_matrix[i][i]
                for k in range(i, self.cols + 1):
                    augmented_matrix[j][k] -= factor * augmented_matrix[i][k]

        # Обратный ход метода Гаусса
        solutions = [0] * self.rows
        for i in range(self.rows - 1, -1, -1):
            solutions[i] = augmented_matrix[i][self.cols]
            for j in range(i + 1, self.rows):
                solutions[i] -= augmented_matrix[i][j] * solutions[j]
            solutions[i] /= augmented_matrix[i][i]

        return solutions

    def solve_iterative(self, constants, max_iterations=100000000000, tolerance=1e-6):
        if self.rows != self.cols:
            raise ValueError("Matrix make be like rectangle")
        if len(constants) != self.rows:
            raise ValueError("Count const make be equally equation")

        # Итерационная матрица и вектор
        iteration_matrix = Matrix(self.rows, self.cols)
        for i in range(self.rows):
            for j in range(self.cols):
                if i == j:
                    iteration_matrix[i][j] = 1 / self.data[i][j]
                else:
                    iteration_matrix[i][j] = -self.data[i][j] / self.data[i][i]

        iteration_vector = [constant / self.data[i][i] for i, constant in enumerate(constants)]

        # Начальное приближение
        current_solution = [0] * self.rows

        for iteration in range(max_iterations):
            next_solution = [0] * self.rows
            for i in range(self.rows):
                next_solution[i] = sum(iteration_matrix[i][j] * current_solution[j] for j in range(self.cols))
                next_solution[i] += iteration_vector[i]

            # Проверка сходимости
            if all(abs(next_solution[i] - current_solution[i]) < tolerance for i in range(self.rows)):
                return next_solution

            current_solution = next_solution

        raise ValueError("Max count operation")

    def copy(self):
        return Matrix(self.rows, self.cols, [row.copy() for row in self.data])


coefficients_matrix = Matrix(4, 4, [[2, -1, 1, 3], [-1, 2, -1, 3], [1, -1, 2, 3], [3, 2, 1 ,-1]])

# Вектор b
constants_vector = [8, -5, 3, 2]

#Крамер
cramer_solution = coefficients_matrix.solve_cramer(constants_vector)
print("Method Cramera:", cramer_solution)

#Гаусс
gauss_solution = coefficients_matrix.solve_gauss(constants_vector)
print("Method Gausa:", gauss_solution)

# Решаем систему уравнений методом простых итераций
iterative_solution = coefficients_matrix.solve_iterative(constants_vector)
print("Method simple itteration:", iterative_solution)
