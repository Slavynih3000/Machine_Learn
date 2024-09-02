from matplotlib import pyplot as plt
import numpy as np

def export(filename):
    log = []
    with open(filename) as f:
        for i in f:
            log.append(float(i))
        return log

def osred(array):
    return sum(array) / len(array)

def main():
    x = (export("log.txt"))
    y = [osred(export("1.txt")), osred(export("2.txt")), osred(export("3.txt"))]

    plt.plot(x, y, c='red')
    plt.plot(x, pryamaya(x, y), c='yellow')
    plt.show()

def pryamaya(x, y):
    x1 = sum(x) / len(x)
    y1 = sum(y) / len(y)

    a1 = np.dot(x, y) / len(x)
    a2 = np.dot(x, x) / len(x)

    k = (a1 - x1 * y1) / (a2 - x1 ** 2)
    b = y1 - k * x1

    kxb = []
    for i in (x):
        kxb.append(k * i + b)
    return kxb

if __name__ == '__main__':
    main()