"""
import ctypes

from multiply import std_mpl
from time_test import random_mtr

libc = ctypes.CDLL('./c_time.so')
a = random_mtr(80)
b = random_mtr(80)

res = []

while len(res) < 10:
    t = libc.tick()
    std_mpl(a, b)
    t -= libc.tick()
    tm = t / (3.5 * 10**9)
    if tm > 0:
        res.append(tm)

print(res)
"""
from multiply import std_mpl
import timeit


def func_test():
    REP = 10
    NUM = 3

    SETUP_CODE = "print('henlo')"

    TEST_CODE = "1823918239813.345 / 4234523422.6756"

    times = timeit.repeat(setup=SETUP_CODE,
                          stmt=TEST_CODE,
                          repeat=REP,
                          number=NUM)
    print(times)
    res = (sum(times) / REP) / NUM

    return res

func_test()


