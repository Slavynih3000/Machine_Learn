import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import poisson

num = int(input("введите число: "))

inputD = np.random.poisson(4, num)
First = np.random.poisson(5, num)
Second = np.random.poisson(5, num)
T1 = []
T2 = []
Ocher4S = 0
Ocher = 0

for i in range(num):
    inputR = inputD[i] + Ocher
    if inputR > First[i]:
        Ocher4S = inputR - First[i]
        if Ocher4S > Second[i]:
            Ocher = Ocher4S - Second[i]
            T2.append(1)
            T1.append(1)

        else:
            T2.append(Ocher4S / Second[i])
            T1.append(1)

    elif inputR == First[i] and inputR != 0:
        T2.append(0)
        T1.append(1)

    else:
        T2.append(0)
        T1.append(inputR / First[i])

t2 = sum(T2)
t0 = num - sum(T1)
t1 = num - t2 - t0
t = t2 + t1 + t0

P2 = t2 / t
P1 = t1 / t
P0 = t0 / t

po = (sum(inputD) / num) / ((sum(First) + sum(Second)) / num)
p0 = (1 + po + (po ** 2) / 2) ** (-1)
p1 = po * p0
p2 = ((po ** 2) / 2) * p0
print("эрланга P0: ", p0)
print("эрланга P1: ", p1)
print("эрланга P2: ", p2)
print("эрланга summa: ", p1 + p0 + p2)

# po = (sum(inputD)) /(sum(First) + sum(Second))
# p0 = (1 + po + (po ** 2)/2)**(-1)
# p1 = po*p0
# p2 = ((po**2)/2)*p0
# print("эрланга P0: ", p0)
# print("эрланга P1: ", p1)
# print("эрланга P2: ", p2)
# print("эрланга summa: ", p1+p0+p2)

# for i in range(num):
#     po = (inputD[i]) /(First[i] + Second[i])
#     p0 = (1 + po + (po ** 2)/2)**(-1)
#     p1 = po*p0
#     p2 = ((po**2)/2)*p0
#     print("эрланга P0: ", p0)
#     print("эрланга P1: ", p1)
#     print("эрланга P2: ", p2)
#     print("эрланга summa: ", p1+p0+p2)

print("входная загрузка:   ", inputD)
print("возможности первой: ", First)
print("возможности второй: ", Second)
print("шансы 1: ", T1)
print("шансы 2: ", T2)
print("вероятность работы всех станций: ", P2)
print("вероятность работы одной станции: ", P1)
print("вероятность работы нуля станций: ", P0)
print("вероятность  общая: ", P0 + P1 + P2)