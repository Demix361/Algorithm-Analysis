from random import randint
from time import time


def mpl(mtr_1, mtr_2):
    row_1 = len(mtr_1)
    col_1 = row_2 = len(mtr_1[0])
    col_2 = len(mtr_2[0])

    res = [[0 for j in range(col_2)] for i in range(row_1)]

    for i in range(row_1):
        for j in range(col_2):
            for k in range(col_1):
                res[i][j] += mtr_1[i][k] * mtr_2[k][j]

    return res


def winograd(mtr_1, mtr_2):
    row_1 = len(mtr_1)
    col_1 = row_2 = len(mtr_1[0])
    col_2 = len(mtr_2[0])

    res = [[0 for j in range(col_2)] for i in range(row_1)]

    mul_h = [0 for i in range(row_1)]
    mul_v = [0 for i in range(col_2)]

    for i in range(row_1):
        for j in range(col_1 // 2):
            mul_h[i] += mtr_1[i][j * 2] * mtr_1[i][j * 2 + 1]

    for i in range(col_2):
        for j in range(row_2 // 2):
            mul_v[i] += mtr_2[j * 2][i] * mtr_2[j * 2 + 1][i]

    for i in range(row_1):
        for j in range(col_2):
            res[i][j] = -mul_h[i] - mul_v[j]
            for k in range(col_1 // 2):
                res[i][j] += (mtr_1[i][2 * k + 1] + mtr_2[2 * k][j]) * \
                             (mtr_1[i][2 * k] + mtr_2[2 * k + 1][j])

    if col_1 % 2 == 1:
        for i in range(row_1):
            for j in range(col_2):
                res[i][j] += mtr_1[i][col_1 - 1] * mtr_2[col_1 - 1][j]

    return res


def winograd_opt(mtr_1, mtr_2):
    row_1 = len(mtr_1)
    col_1 = row_2 = len(mtr_1[0])
    col_2 = len(mtr_2[0])

    col_1_mod = row_2_mod = col_1 % 2

    res = [[0 for j in range(col_2)] for i in range(row_1)]

    mul_h = [0 for i in range(row_1)]
    mul_v = [0 for i in range(col_2)]

    for i in range(row_1):
        for j in range(0, col_1 - col_1_mod, 2):
            mul_h[i] += mtr_1[i][j] * mtr_1[i][j + 1]

    for i in range(col_2):
        for j in range(0, row_2 - row_2_mod, 2):
            mul_v[i] += mtr_2[j][i] * mtr_2[j + 1][i]

    for i in range(row_1):
        for j in range(col_2):
            buff = - mul_h[i] - mul_v[j]
            for k in range(0, col_1 - col_1_mod, 2):
                buff += (mtr_1[i][k + 1] + mtr_2[k][j]) * \
                             (mtr_1[i][k] + mtr_2[k + 1][j])
            res[i][j] = buff

    if col_1 % 2 == 1:
        col_1_min = col_1 - 1
        for i in range(row_1):
            for j in range(col_2):
                res[i][j] += mtr_1[i][col_1_min] * mtr_2[col_1_min][j]

    return res


def main():
    n = 100
    a = [[randint(0, 100) for j in range(n)] for i in range(n)]
    b = [[randint(0, 100) for j in range(n)] for i in range(n)]

    beg = time()
    res_1 = mpl(a, b)
    print(time() - beg)

    beg = time()
    res_2 = winograd(a, b)
    print(time() - beg)

    beg = time()
    res_3 = winograd_opt(a, b)
    print(time() - beg)

    print(res_1 == res_2 == res_3)


if __name__ == '__main__':
    main()
