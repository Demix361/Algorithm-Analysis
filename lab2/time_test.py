from time import time
from random import choice, randint
from multiply import std_mpl, winograd, winograd_opt


def random_mtr(size):
    res = [[randint(-50, 50) for j in range(size)] for i in range(size)]

    return res


def test_one_size(size):
    mtr_1 = random_mtr(size)
    mtr_2 = random_mtr(size)
    res = []

    beg = time()
    std_mpl(mtr_1, mtr_2)
    res.append(time() - beg)

    beg = time()
    winograd(mtr_1, mtr_2)
    res.append(time() - beg)

    beg = time()
    winograd_opt(mtr_1, mtr_2)
    res.append(time() - beg)

    return res


def res_to_file(table, f_1, f_2, f_3):
    with open(f_1, 'w') as f:
        for i in range(len(table)):
            f.write(str(table[i][0]) + ' ' + str(table[i][1][0]) + '\n')

    with open(f_2, 'w') as f:
        for i in range(len(table)):
            f.write(str(table[i][0]) + ' ' + str(table[i][1][1]) + '\n')

    with open(f_3, 'w') as f:
        for i in range(len(table)):
            f.write(str(table[i][0]) + ' ' + str(table[i][1][2]) + '\n')


def test(beg, step, times, prefix):
    table = []

    for i in range(times):
        table.append((beg, test_one_size(beg)))
        beg += step

    res_to_file(table,
                'res_std' + prefix + '.txt',
                'res_win' + prefix + '.txt',
                'res_win_opt' + prefix + '.txt')


if __name__ == "__main__":
    test(100, 100, 5, '0')
    test(101, 100, 5, '1')

