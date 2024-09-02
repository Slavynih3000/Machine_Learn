import numpy as np
import matplotlib.pyplot as plt
from matplotlib.path import Path
from matplotlib.patches import Polygon

def activation(x):
    return not (0.2 < x < 0.7)

def forward(xs, weights):#скалярное произведение векторов
    return [activation(value) for value in np.dot(weights, xs)]

N = 1000

x1, x2, x3 = np.random.random(N), np.random.random(N), [1] * N
X = np.array([x1, x2, x3])

w1 = np.random.rand(3)
w2 = np.random.rand(3)
w3 = np.random.rand(3)
w4 = np.random.rand(3)
w5 = np.random.rand(3)
w6 = np.random.rand(3)
w7 = np.random.rand(3)
w8 = np.random.rand(3)

r1, r2 = forward(X, w1), forward(X, w2)
r3, r4 = forward(X, w3), forward(X, w4)
r5, r6 = forward(X, w5), forward(X, w6)
r7, r8 = forward(X, w7), forward(X, w8)


vertices = np.array([[0.4, 0.0], [0.1, 0.4], [0.1, 0.6], [0.4, 1.0],
                     [0.6, 1.0], [0.9, 0.6], [0.9, 0.4], [0.6, 0.0]])

polygon = Path(vertices)

fig, ax = plt.subplots()
patch = Polygon(vertices, edgecolor='blue', facecolor='none')
ax.add_patch(patch)

for i in range(N):
    if polygon.contains_point([x1[i], x2[i]]):
        plt.scatter(x1[i], x2[i], c="green")
    else:
        plt.scatter(x1[i], x2[i], c="red")

plt.show()
