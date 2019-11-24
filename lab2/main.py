from random import randint


def print_mtr(mtr):
    for line in mtr:
        for el in line:
            print(el, end=' ')
        print()
    print()


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


def gen_mtr(row, col):
    mtr = [[randint(0, 100) for j in range(col)] for i in range(row)]

    return mtr


def check_mtr(row_1, col_1, row_2, col_2):
    if col_1 != row_2:
        return False
    if row_1 <= 1 or col_1 <= 1 or row_2 <= 1 or col_2 <= 1:
        return False

    return True


def main():
    choice = input('1 - input matrices from file\n'
                   '2 - generate random matrices\n'
                   'Input: ')

    if choice == '1':
        fname_1 = input('Введите имя первого файла: ')
        fname_2 = input('Введите имя второго файла: ')

        mtr_1 = mtr_from_file(fname_1)
        mtr_2 = mtr_from_file(fname_2)

        if mtr_1 is None or mtr_2 is None:
            print('Ошибка чтения файлов.')
            return

        if not check_mtr(len(mtr_1), len(mtr_1[0]), len(mtr_2), len(mtr_2[0])):
            print('Невозсожно умножить матрицы с такой размерностью.')
            return
    elif choice == '2':
        row_1 = input('Input 1 matrix raw number: ')
        col_1 = input('Input 1 matrix column number: ')
        row_2 = input('Input 2 matrix raw number: ')
        col_2 = input('Input 2 matrix column number: ')

        try:
            row_1 = int(row_1)
            col_1 = int(col_1)
            row_2 = int(row_2)
            col_2 = int(col_2)
        except ValueError:
            print('Неверный ввод.')
            return

        if not check_mtr(row_1, col_1, row_2, col_2):
            print('Невозсожно умножить матрицы с такой размерностью.')
            return

        mtr_1 = gen_mtr(row_1, col_1)
        mtr_2 = gen_mtr(row_2, col_2)
    else:
        print('Incorrect input.')
        return

    mtr = mpl(mtr_1, mtr_2)
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
