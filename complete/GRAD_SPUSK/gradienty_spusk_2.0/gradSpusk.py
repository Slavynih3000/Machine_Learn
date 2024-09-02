#библиотека какая о пропущена
from matplotlib import pyplot as axes
import numpy as np
import math
#ploting our canvas
#plt.plot([1,2,3],[4,5,1])
#display the graph
#plt.show()

def xproiz(x, y):#(3x^2*y^3)
    return 6*x*y**3#3*x**2 + 2*x*y**3

def yproiz(x, y):
    return 9*x**2*y**2#2*y + 3*x**2*y**2
#def zproiz(x,y):
 #   return 3*x**2*y**3

e = 0.001
h = 0.0001
x = 1
y = 1
xpr = 0
ypr = 0
zpr = 0
while ((x-xpr)**2+(y-ypr)**2)**0.5 > 0.0001:
    xpr = x
    ypr = y
    x = x - e*xproiz(x,y)
    y = y - e*yproiz(x,y)
print("X = ", x, "Y = ", y)
l=x
m=y
z=0
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(l, m, color='red', marker='o', label='Точка')
x = np.linspace(-10, 10, 100)
y = np.linspace(-10, 10, 100)


x, y = np.meshgrid(x, y)

# Вычисляем значения функции z = 3x^2y^3
z = 3 * x**2 * y**3



ax.plot_surface(x, y, z, cmap='viridis')




ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')


plt.show()