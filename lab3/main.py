from sorts import bubble_sort, bubble_barrier_sort, shaker_sort


def main():
    while True:
        line = input('Введите массив: ')

        try:
            arr = list(map(int, line.split()))

            if len(arr) == 0:
                print('Пустой массив.')
            else:
                print('\nСортировка пузырьком: ')
                print(bubble_sort(arr.copy()))

                print('Сортировка пузырьком с барьером: ')
                print(bubble_barrier_sort(arr.copy()))

                print('Сортировка шейкером: ')
                print(shaker_sort(arr.copy()), '\n')
        except ValueError:
            print('Ошибка ввода.')


if __name__ == '__main__':
    main()
