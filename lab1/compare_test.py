from random import randint
from time import time
from main import lev_table, dam_lev_table, dam_lev_recursion


def get_args(line):
	arr = line[:-1].split(",")

	return arr[0], arr[1], int(arr[2]), int(arr[3])


def test(str_1, str_2, lev_expect, dam_lev_expect):
	lev = lev_table(str_1, str_2)
	dam_lev_tab = dam_lev_table(str_1, str_2)
	dam_lev_rec = dam_lev_recursion(str_1, str_2)
	count = 0

	print("str_1: '", str_1, "'\t\tstr_2: '", str_2, "'", sep="")
	
	if lev == lev_expect:
		print("Тест на Левенштейне(итеративном) успешен! [%s]" % lev_expect)
		count += 1
	else:
		print("Тест на Левенштейне(итеративном) провален. Ожидаемый результат: ", lev_expect, "полученный: ", lev)
	
	if dam_lev_tab == dam_lev_rec == dam_lev_expect:
		print("Тест на Дамерау-Левенштейне успешен! [%s]" % dam_lev_expect)
		count += 1
	else:
		print("Тест на Дамерау-Левенштейне провален. Ожидаемый результат: ", dam_lev_expect, "итеративный: ", dam_lev_tab, "рекурсивный: ", dam_lev_rec)
	print()

	return count


if __name__ == "__main__":
	with open("compare_test.txt", "r") as f:
		count = 0
		succ = 0

		for line in f:
			str_1, str_2, lev, dam_lev = get_args(line)
			succ += test(str_1, str_2, lev, dam_lev)
			count += 2

		print(succ, " из ", count, " тестов прошли успешно!")
