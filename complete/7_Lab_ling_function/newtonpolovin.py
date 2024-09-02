def main():#7 нахождение нулей функции на отрезке лаба 7
    f = lambda x: x**3 + 4.0 * x - 3.0

    a = -10.0  # Левая граница интервала
    b = 10.0   # Правая граница интервала
    epsilon = 1e-6  # Заданная точность

    root_bisection = find_root_bisection(f, a, b, epsilon)
    print("Приближенный корень с использованием половинного деления:", root_bisection)

    root_newton = find_root_newton(f, 0.0, epsilon)
    print("Приближенный корень с использованием метода Ньютона:", root_newton)

def find_root_bisection(f, a, b, epsilon):
    while b - a > epsilon:
        midpoint = (a + b) / 2.0
        if f(midpoint) == 0.0:
            # Найден корень
            return midpoint
        elif f(a) * f(midpoint) < 0.0:
            b = midpoint
        else:
            a = midpoint

    return (a + b) / 2.0

def find_root_newton(f, x0, epsilon):
    x = x0
    while abs(f(x)) > epsilon:
        derivative = (f(x + epsilon) - f(x)) / epsilon
        x = x - f(x) / derivative

    return x

if __name__ == "__main__":
    main()
