import timeit
from time import time
from random import choice
from main import lev_table, dam_lev_table, dam_lev_recursion
from prettytable import PrettyTable
import matplotlib.pyplot as plt


def random_str(size):
    abc = "qwertyuiopasdfghjklzxcvbnm"
    res = ""

    for i in range(size):
        res += choice(abc)

    return res


def func_test(word_size, func_name):
    REP = 100
    NUM = 100

    SETUP_CODE = "from __main__ import " + func_name + ", random_str\nstr_1 = '" \
                 + str(random_str(word_size)) + "'\n" \
                 + "str_2 = '" + str(random_str(word_size)) + "'"

    TEST_CODE = func_name + "(str_1, str_2)"

    times = timeit.repeat(setup=SETUP_CODE,
                          stmt=TEST_CODE,
                          repeat=REP,
                          number=NUM)

    res = (sum(times) / REP) / NUM

    return res


def get_table(res):
    tab = PrettyTable()
    column_names = ["lev_table", "dam_lev_table", "dam_lev_recursion"]

    tab.add_column("word_length", [i for i in range(2, len(res[0]) + 2, 1)])

    for i in range(len(res)):
        tab.add_column(column_names[i], res[i])

    return tab


def test(max_len):
    result = [[], [], []]

    for i in range(2, max_len + 1, 1):
        beg = time()
        result[0].append(func_test(i, "lev_table"))
        result[1].append(func_test(i, "dam_lev_table"))
        result[2].append(func_test(i, "dam_lev_recursion"))
        print(i, " done! [", time() - beg, "]", sep="")

    table = get_table(result)
    print(table)

    length = [i for i in range(2, max_len + 1, 1)]

    plt.plot(length, result[0], 'r', label="lev_tab")
    plt.plot(length, result[1], 'b', label="dam_lev_tab")
    plt.legend(loc='upper left')
    plt.axis([length[0], length[-1], min(result[0] + result[1]), max(result[0] + result[1])])
    plt.grid(True)
    plt.show()

    plt.plot(length, result[2], 'g', label="dam_lev_rec")
    plt.plot(length, result[1], 'b', label="dam_lev_tab")
    plt.legend(loc='upper left')
    plt.axis([length[0], length[-1], min(result[2] + result[1]), max(result[2] + result[1])])
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    # max = 7 takes about 18 minutes to calculate
    test(4)
