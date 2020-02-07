from sorts import bubble_sort, bubble_barrier_sort, shaker_sort
from prettytable import PrettyTable
import timeit
from random import randint


def test_on_arr(arr, f_name):
    repeat = 10

    x = "["
    for n in arr:
        x += str(n)
        x += ", "
    x += "]"

    setup_code = "from __main__ import " + f_name + "\n"\
        "arr = " + x

    test_code = f_name + "(arr)"

    times = timeit.repeat(setup=setup_code,
                          stmt=test_code,
                          repeat=repeat,
                          number=1)

    res = sum(times) / repeat

    return res


def test_sort(beg, end, step, sort_name):
    res = []

    for i in range(beg, end, step):
        arr_rnd = [randint(-1000, 1000) for j in range(i)]
        arr_inc = sorted(arr_rnd)
        arr_dec = sorted(arr_rnd, reverse=True)

        res.append([])
        res[-1].append(test_on_arr(arr_rnd, sort_name))
        res[-1].append(test_on_arr(arr_inc, sort_name))
        res[-1].append(test_on_arr(arr_dec, sort_name))
        print(i, 'done')

    tab = PrettyTable()
    tab.field_names = ["arr_size", "random", "increasing", "decreasing"]
    b = beg
    for i in range(len(res)):
        res[i].insert(0, b)
        tab.add_row(res[i])
        b += step

    return tab, res


def test_all(beg, end, step):
    table_bubble, mtr_bubble = test_sort(beg, end, step, 'bubble_sort')
    write_res('Report/bubble', mtr_bubble)
    print('Bubble sort')
    print(table_bubble)

    table_bubble_bar, mtr_bubble = test_sort(beg, end, step, 'bubble_barrier_sort')
    write_res('Report/bubble_bar', mtr_bubble)
    print('Bubble with barrier sort')
    print(table_bubble_bar)

    table_shaker, mtr_bubble = test_sort(beg, end, step, 'shaker_sort')
    write_res('Report/shaker', mtr_bubble)
    print('Shaker sort')
    print(table_shaker)


def write_res(fname, res):
    with open(fname + '_rnd.txt', 'w') as f:
        for line in res:
            f.write(str(line[0]) + ' ' + str(line[1]) + '\n')

    with open(fname + '_inc.txt', 'w') as f:
        for line in res:
            f.write(str(line[0]) + ' ' + str(line[2]) + '\n')

    with open(fname + '_dec.txt', 'w') as f:
        for line in res:
            f.write(str(line[0]) + ' ' + str(line[3]) + '\n')


if __name__ == '__main__':
    test_all(100, 801, 100)
