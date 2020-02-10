from random import randint
from time import time, sleep
from threading import Thread


class MyThread(Thread):
    def __init__(self, r_1, r_2, c_1, c_2, res, mtr_1, mtr_2):
        Thread.__init__(self)
        self.r_1 = r_1
        self.r_2 = r_2
        self.c_1 = c_1
        self.c_2 = c_2
        self.res = res
        self.mtr_1 = mtr_1
        self.mtr_2 = mtr_2

    def run(self):
        for i in range(self.r_1, self.r_2, 1):
            for j in range(self.c_1, self.c_2, 1):
                self.res[i][j] = self.mtr_1[i][j] + self.mtr_2[i][j]


def create_threads():
    for i in range(50):
        name = "Thread #%s" % (i + 1)
        my_thread = MyThread(name)
        my_thread.start()


def mtr_sum(mtr_1, mtr_2):
    row = len(mtr_1)
    col = len(mtr_1[0])

    res = [[0 for j in range(col)] for i in range(row)]

    for i in range(row):
        for j in range(col):
            res[i][j] = mtr_1[i][j] + mtr_2[i][j]

    return res


def get_mtr(size):
    res = [[randint(-10000, 10000) for j in range(size)] for i in range(size)]

    return res


def mtr_sum_4th(mtr_1, mtr_2):
    row = len(mtr_1)
    col = len(mtr_1[0])

    r_1 = row // 2
    c_1 = col // 2

    res = [[0 for j in range(col)] for i in range(row)]

    th_1 = MyThread(0, r_1, 0, c_1, res, mtr_1, mtr_2)
    th_2 = MyThread(0, r_1, c_1, col, res, mtr_1, mtr_2)
    th_3 = MyThread(r_1, row, 0, c_1, res, mtr_1, mtr_2)
    th_4 = MyThread(r_1, row, c_1, col, res, mtr_1, mtr_2)

    th_1.start()
    th_2.start()
    th_3.start()
    th_4.start()

    return res


def main_d():
    mtr_1 = get_mtr(1000)
    mtr_2 = get_mtr(1000)

    beg = time()
    res = mtr_sum(mtr_1, mtr_2)
    print(time() - beg)
    print(res[56][78])


def main_t():
    mtr_1 = get_mtr(1000)
    mtr_2 = get_mtr(1000)

    beg = time()
    res = mtr_sum_4th(mtr_1, mtr_2)
    print(time() - beg)
    print(res[56][78])


if __name__ == "__main__":
    main_d()

