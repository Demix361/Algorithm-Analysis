from random import randint
from time import time, sleep
from threading import Thread


class MulHThread(Thread):
    def __init__(self, len_1, len_2, vec, mtr):
        Thread.__init__(self)
        self.len_1 = len_1
        self.len_2 = len_2
        self.vec = vec
        self.mtr = mtr

    def run(self):
        for i in range(self.len_1):
            for j in range(0, self.len_2, 2):
                self.vec[i] += self.mtr[i][j] * self.mtr[i][j + 1]


class MulVThread(Thread):
    def __init__(self, len_1, len_2, vec, mtr):
        Thread.__init__(self)
        self.len_1 = len_1
        self.len_2 = len_2
        self.vec = vec
        self.mtr = mtr

    def run(self):
        for i in range(self.len_1):
            for j in range(0, self.len_2, 2):
                self.vec[i] += self.mtr[j][i] * self.mtr[j + 1][i]


class TripleLoopThread(Thread):
    def __init__(self, row_1, col_2, len_mid, mul_h, mul_v, mtr_1, mtr_2, res, th_num, th_amount):
        Thread.__init__(self)
        self.row_1 = row_1
        self.col_2 = col_2
        self.len_mid = len_mid
        self.mul_h = mul_h
        self.mul_v = mul_v
        self.mtr_1 = mtr_1
        self.mtr_2 = mtr_2
        self.res = res
        self.th_num = th_num
        self.th_amount = th_amount

    def run(self):
        for i in range(self.th_num, self.row_1, self.th_amount):
            for j in range(self.col_2):
                buff = - self.mul_h[i] - self.mul_v[j]
                for k in range(0, self.len_mid, 2):
                    buff += (self.mtr_1[i][k + 1] + self.mtr_2[k][j]) * \
                            (self.mtr_1[i][k] + self.mtr_2[k + 1][j])
                self.res[i][j] = buff


def get_mtr(size):
    res = [[randint(-10000, 10000) for j in range(size)] for i in range(size)]

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

    print(mul_h)
    print(mul_v)

    for i in range(row_1):
        for j in range(col_2):
            buff = - mul_h[i] - mul_v[j]
            for k in range(0, col_1 - col_1_mod, 2):
                buff += (mtr_1[i][k + 1] + mtr_2[k][j]) * \
                        (mtr_1[i][k] + mtr_2[k + 1][j])
            res[i][j] = buff

    if col_1_mod == 1:
        col_1_min = col_1 - 1
        for i in range(row_1):
            for j in range(col_2):
                res[i][j] += mtr_1[i][col_1_min] * mtr_2[col_1_min][j]

    return res


def winograd_threading(mtr_1, mtr_2, threads):
    row_1 = len(mtr_1)
    col_1 = row_2 = len(mtr_1[0])
    col_2 = len(mtr_2[0])
    col_1_mod = row_2_mod = col_1 % 2

    res = [[0 for j in range(col_2)] for i in range(row_1)]
    mul_h = [0 for i in range(row_1)]
    mul_v = [0 for i in range(col_2)]

    mul_h_thread = MulHThread(row_1, col_1 - col_1_mod, mul_h, mtr_1)
    mul_v_thread = MulVThread(col_2, row_2 - row_2_mod, mul_v, mtr_2)

    mul_h_thread.start()
    mul_v_thread.start()

    print(mul_h)
    print(mul_v)

    for i in range(threads):
        loop_thread = TripleLoopThread(row_1, col_2, col_1 - col_1_mod, mul_h, mul_v, mtr_1, mtr_2, res, i, threads)
        loop_thread.start()

    if col_1_mod == 1:
        col_1_min = col_1 - 1
        for i in range(row_1):
            for j in range(col_2):
                res[i][j] += mtr_1[i][col_1_min] * mtr_2[col_1_min][j]

    return res



def main():
    a = get_mtr(200)
    b = get_mtr(200)

    beg = time()
    res_1 = winograd_opt(a, b)
    print(time() - beg)

    beg = time()
    res_2 = winograd_threading(a, b, 10)
    print(time() - beg)

    print(res_1[45])
    print(res_2[45])


if __name__ == '__main__':
    main()
