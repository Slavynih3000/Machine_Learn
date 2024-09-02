from matplotlib import pyplot as plt
import numpy as np
import math
x = 1
def func(x):
   return x**2
def trapezoidal_rule(func, a, b, tolerance=1e-6):
    n = 1
    h = (b - a) / n
    integral_prev = 0
    integral = 0.5 * (func(a) + func(b))

    while abs(integral - integral_prev) > tolerance:
        integral_prev = integral
        n *= 2
        h = (b - a) / n
        integral = 0.5 * (func(a) + func(b))

        for i in range(1, n):
            x_i = a + i * h
            integral += func(x_i)

        integral *= h

    return integral

def simpson_rule(func, a, b, tolerance=1e-6):
    n = 2
    h = (b - a) / n
    integral_prev = 0
    integral = func(a) + func(b)

    while abs(integral - integral_prev) > tolerance:
        integral_prev = integral
        n *= 2
        h = (b - a) / n
        integral = func(a) + func(b)

        for i in range(1, n):
            x_i = a + i * h
            if i % 2 == 0:
                integral += 2 * func(x_i)
            else:
                integral += 4 * func(x_i)

        integral *= h / 3

    return integral
a = 2.0  # Нижний предел интегрирования
b = 5.0  # Верхний предел интегрирования

result_trapezoidal = trapezoidal_rule(target_function, a, b)
print(f"Результат интегрирования (метод трапеций): {result_trapezoidal}")

result_simpson = simpson_rule(target_function, a, b)
print(f"Результат интегрирования (метод Симпсона): {result_simpson}")

