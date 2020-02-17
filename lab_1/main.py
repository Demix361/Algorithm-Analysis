def print_matrix(m):
    for i in range(len(m)):
        for j in range(len(m[i])):
            print(m[i][j], end=" ")
        print()
    print()


def lev_table(str_1, str_2):
    len_1 = len(str_1)
    len_2 = len(str_2)
    table = [[0 for j in range(len_2 + 1)] for i in range(len_1 + 1)]

    # Тривиальные случаи
    for i in range(len_1):
        table[i + 1][0] = table[i][0] + 1

    for i in range(len_2):
        table[0][i + 1] = table[0][i] + 1

    # Остальные случаи
    for i in range(1, len_1 + 1, 1):
        for j in range(1, len_2 + 1, 1):
            step_1 = table[i - 1][j] + 1
            step_2 = table[i][j - 1] + 1

            if str_1[i - 1] == str_2[j - 1]:
                diag = 0
            else:
                diag = 1

            step_3 = table[i - 1][j - 1] + diag

            table[i][j] = min(step_1, step_2, step_3)

    print_matrix(table)
    return table[len_1][len_2]


# not used
def lev_recursion(str_1, str_2):
    if len(str_1) == 0:
        return len(str_2)
    elif len(str_2) == 0:
        return len(str_1)
    else:
        if str_1[-1] == str_2[-1]:
            diag = 0
        else:
            diag = 1

        d = min(lev_recursion(str_1, str_2[:-1]) + 1,
                lev_recursion(str_1[:-1], str_2) + 1,
                lev_recursion(str_1[:-1], str_2[:-1]) + diag)

        return d


def dam_lev_table(str_1, str_2):
    len_1 = len(str_1)
    len_2 = len(str_2)
    table = [[0 for j in range(len_2 + 1)] for i in range(len_1 + 1)]

    # Тривиальные случаи
    for i in range(len_1):
        table[i + 1][0] = table[i][0] + 1

    for i in range(len_2):
        table[0][i + 1] = table[0][i] + 1

    # Остальные случаи
    for i in range(1, len_1 + 1, 1):
        for j in range(1, len_2 + 1, 1):
            step_1 = table[i - 1][j] + 1
            step_2 = table[i][j - 1] + 1

            if str_1[i - 1] == str_2[j - 1]:
                diag = 0
            else:
                diag = 1

            step_3 = table[i - 1][j - 1] + diag

            if i - 2 >= 0 and j - 2 >= 0 and str_1[i - 1] == str_2[j - 2] and str_1[i - 2] == str_2[j - 1]:
                step_4 = table[i - 2][j - 2] + 1
                table[i][j] = min(step_1, step_2, step_3, step_4)
            else:
                table[i][j] = min(step_1, step_2, step_3)

    return table[len_1][len_2]


def dam_lev_recursion(str_1, str_2):
    if len(str_1) == 0:
        return len(str_2)

    elif len(str_2) == 0:
        return len(str_1)

    else:
        if str_1[-1] == str_2[-1]:
            diag = 0
        else:
            diag = 1

        step_1 = dam_lev_recursion(str_1, str_2[:-1]) + 1
        step_2 = dam_lev_recursion(str_1[:-1], str_2) + 1
        step_3 = dam_lev_recursion(str_1[:-1], str_2[:-1]) + diag
        step_4 = dam_lev_recursion(str_1[:-2], str_2[:-2]) + 1

        if len(str_1) > 1 and len(str_2) > 1 and str_1[-1] == str_2[-2] and str_1[-2] == str_2[-1]:
            d = min(step_1, step_2, step_3, step_4)
        else:
            d = min(step_1, step_2, step_3)

        return d


def main():
    while True:
        str_1 = input("Введите первое слово: ")
        str_2 = input("Введите второе слово: ")

        menu = "1 - Ливенштейн(итеративно)\n" \
        "2 - Ливенштейн-Дамерау(итеративно)\n"\
        "3 - Ливенштейн-Дамерау(рекурсивно)\n"\
        "0 - выход"

        print(menu)

        while True:
            choice = input("Выберите пункт меню: ")
            try:
                choice = int(choice)

                if 0 <= choice <= 3:
                    break
                else:
                    print("Неверное число!")
            except ValueError:
                print("Неверный выбор!")
        if choice == 1:
            d = lev_table(str_1, str_2)
        elif choice == 2:
            d = dam_lev_table(str_1, str_2)
        elif choice == 3:
            d = dam_lev_recursion(str_1, str_2)
        else:
            break

        print("Штраф: ", d, "\n")


if __name__ == "__main__":
    main()
