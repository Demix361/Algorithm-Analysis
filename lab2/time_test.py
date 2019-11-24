import timeit
from time import time
from random import choice, randint
from main import mpl, winograd, winograd_opt
from prettytable import PrettyTable
import matplotlib.pyplot as plt


def random_mtr(size):
    res = [[randint(0, 100) for j in range(size)] for i in range(size)]

    return res


def test_all(size):
    res = []




def get_table(res):
    tab = PrettyTable()
    column_names = ["standart_mpl", "winograd_mpl", "winograd_opt_mpl"]

    tab.add_column("matrix_size", [i for i in range(2, len(res[0]) + 2, 1)])

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
