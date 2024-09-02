import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline
np.random.seed(1000)
num_points = 25
x = np.sort(np.random.uniform(0, 10, num_points))
y = np.random.uniform(0, 10, num_points)
cs = CubicSpline(x, y)
x_new = np.linspace(min(x), max(x), 1000)
y_new = cs(x_new)
plt.scatter(x, y, label='Случайные данные')
plt.plot(x_new, y_new, label='Кубический сплайн', color='red')
plt.legend()
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
