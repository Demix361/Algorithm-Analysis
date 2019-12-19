import multiprocessing
from random import randint


mtr_1 = [[randint(-100, 100) for j in range(300)] for i in range(300)]
mtr_2 = [[randint(-100, 100) for j in range(300)] for i in range(300)]

row_1 = len(mtr_1)
col_1 = row_2 = len(mtr_1[0])
col_2 = len(mtr_2[0])

res = [[0 for j in range(col_2)] for i in range(row_1)]


def std_mpl():
    for i in range(row_1):
        for j in range(col_2):
            for k in range(col_1):
                res[i][j] += mtr_1[i][k] * mtr_2[k][j]

def mpl_1():
    for i in range(0, row_1 // 2, 1):
        for j in range(col_2):
            for k in range(col_1):
                res[i][j] += mtr_1[i][k] * mtr_2[k][j]

def mpl_2():
    for i in range(row_1 // 2, row_1, 1):
        for j in range(col_2):
            for k in range(col_1):
                res[i][j] += mtr_1[i][k] * mtr_2[k][j]
mpl_1()
mpl_2()

