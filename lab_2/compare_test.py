from multiply import std_mpl, winograd, winograd_opt
from main import read_mtr


def write_mtr(fname, mtr):
    row = len(mtr)
    col = len(mtr[0])

    with open(fname, 'w') as f:
        for i in range(row):
            for j in range(col):
                f.write(str(mtr[i][j]) + ' ')
            f.write('\n')


def create_test_files(files):
    for i in range(len(files)):
        mtr_1 = read_mtr(files[i])
        for j in range(i, len(files), 1):
            mtr_2 = read_mtr(files[j])

            mtr_res = winograd_opt(mtr_1, mtr_2)
            fname = 'mtr/mtr_' + str(i) + '_' + str(j)
            write_mtr(fname, mtr_res)


def main():
    files = []
    create_test_files(files)


if __name__ == '__main__':
    main()