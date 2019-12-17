from random import randint
from multiply import std_mpl, winograd, winograd_opt


def print_mtr(mtr):
    for line in mtr:
        for el in line:
            print(el, end=' ')
        print()
    print()


def gen_mtr(row, col):
    mtr = [[randint(0, 100) for j in range(col)] for i in range(row)]

    return mtr


def check_mtr(row_1, col_1, row_2, col_2):
    if col_1 != row_2:
        return False
    if row_1 <= 1 or col_1 <= 1 or row_2 <= 1 or col_2 <= 1:
        return False

    return True


def read_mtr(fname):
    res = []
    try:
        with open(fname, 'r') as f:
            for line in f:
                try:
                    line = list(map(int, line.split(' ')))
                except ValueError:
                    return None
                res.append(line)
    except FileNotFoundError:
        return None

    row_len = len(res[0])
    col_len = len(res)

    if row_len <= 1 or col_len <= 1:
        return None
    for r in res:
        if len(r) != row_len:
            return None

    return res


def fill_mtr(row, col):
    mtr = [[0 for j in range(col)] for i in range(row)]

    for i in range(row):
        while True:
            line = input()
            line = line.split()
            try:
                line = list(map(int, line))
                if len(line) == col:
                    for j in range(col):
                        mtr[i][j] = line[j]
                    break
            except ValueError:
                pass
            print('Неверный ввод, введите строку еще раз.')

    return mtr


def main():
    choice = input('1 - Ввести матрицы из файла\n'
                   '2 - Сгенерировать случайные матрицы\n'
                   '3 - Ввести матрицы вручную\n'
                   'Ввод: ')

    if choice == '1':
        fname_1 = input('Введите имя первого файла: ')
        fname_2 = input('Введите имя второго файла: ')

        mtr_1 = read_mtr(fname_1)
        mtr_2 = read_mtr(fname_2)

        if mtr_1 is None or mtr_2 is None:
            print('Ошибка чтения файлов.')
            return

        if not check_mtr(len(mtr_1), len(mtr_1[0]), len(mtr_2), len(mtr_2[0])):
            print('Невозсожно умножить матрицы с такой размерностью.')
            return
    elif choice == '2':
        row_1 = input('Введите количество строк для 1 матрицы: ')
        col_1 = input('Введите количество столбцов для 1 матрицы: ')
        row_2 = input('Введите количество строк для 2 матрицы: ')
        col_2 = input('Введите количество столбцов для 2 матрицы: ')

        try:
            row_1 = int(row_1)
            col_1 = int(col_1)
            row_2 = int(row_2)
            col_2 = int(col_2)
        except ValueError:
            print('Неверный ввод.')
            return

        if not check_mtr(row_1, col_1, row_2, col_2):
            print('Невозможно умножить матрицы с такой размерностью.')
            return

        mtr_1 = gen_mtr(row_1, col_1)
        mtr_2 = gen_mtr(row_2, col_2)
    elif choice == '3':
        row_1 = input('Введите количество строк для 1 матрицы: ')
        col_1 = input('Введите количество столбцов для 1 матрицы: ')
        row_2 = input('Введите количество строк для 2 матрицы: ')
        col_2 = input('Введите количество столбцов для 2 матрицы: ')

        try:
            row_1 = int(row_1)
            col_1 = int(col_1)
            row_2 = int(row_2)
            col_2 = int(col_2)
        except ValueError:
            print('Неверный ввод.')
            return

        if not check_mtr(row_1, col_1, row_2, col_2):
            print('Невозможно умножить матрицы с такой размерностью.')
            return

        print('\nВведите первую матрицу (%s x %s)' % (row_1, col_1))
        mtr_1 = fill_mtr(row_1, col_1)
        print('\nВведите вторую матрицу (%s x %s)' % (row_2, col_2))
        mtr_2 = fill_mtr(row_2, col_2)
    else:
        print('Неверный ввод.')
        return

    print('Первая матрица:')
    print_mtr(mtr_1)
    print('Вторая матрица:')
    print_mtr(mtr_2)

    mtr = std_mpl(mtr_1, mtr_2)
    print('Умножение матриц стандартным методом:')
    print_mtr(mtr)

    mtr = winograd(mtr_1, mtr_2)
    print('Умножение матриц методом Винограда:')
    print_mtr(mtr)

    mtr = winograd_opt(mtr_1, mtr_2)
    print('Умножение матриц оптимизированным методом Винограда:')
    print_mtr(mtr)


if __name__ == '__main__':
    main()
