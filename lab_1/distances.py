
def l_distance_table(str_1, str_2):
	table = [[0 for j in range(len(str_2) + 1)] for i in range(len(str_1) + 1)]

	# Тривиальные случаи
	for i in range(len(str_1)):
		table[i + 1][0] = table[i][0] + 1

	for i in range(len(str_2)):
		table[0][i + 1] = table[0][i] + 1

	# Остальные случаи
	for i in range(1, len(str_1) + 1, 1):
		for j in range(1, len(str_2) + 1, 1):
			if str_1[i - 1] == str_2[j - 1]:
				diag = 0
			else:
				diag = 1

			table[i][j] = min(table[i - 1][j] + 1, table[i][j - 1] + 1, table[i - 1][j - 1] + diag)

	return table[-1][-1]


def l_distance_recursion(str_1, str_2):
	if len(str_1) == 0:
		return len(str_2)
	elif len(str_2) == 0:
		return len(str_1)
	else:
		if str_1[-1] == str_2[-1]:
			diag = 0
		else:
			diag = 1

		d = min(l_distance_recursion(str_1, str_2[:-1]) + 1,
				l_distance_recursion(str_1[:-1], str_2) + 1,
				l_distance_recursion(str_1[:-1], str_2[:-1]) + diag)

		return d


def d_l_distance_table(str_1, str_2):
	table = [[0 for j in range(len(str_2) + 1)] for i in range(len(str_1) + 1)]

	# Тривиальные случаи
	for i in range(len(str_1)):
		table[i + 1][0] = table[i][0] + 1

	for i in range(len(str_2)):
		table[0][i + 1] = table[0][i] + 1

	# Остальные случаи
	for i in range(1, len(str_1) + 1, 1):
		for j in range(1, len(str_2) + 1, 1):
			if str_1[i - 1] == str_2[j - 1]:
				diag = 0
			else:
				diag = 1

			if i - 2 >= 0 and j - 2 >= 0 and str_1[i - 1] == str_2[j - 2] and str_1[i - 2] == str_2[j - 1]:
				table[i][j] = min(table[i - 1][j] + 1, table[i][j - 1] + 1, table[i - 1][j - 1] + diag, table[i - 2][j - 2] + 1)
			else:
				table[i][j] = min(table[i - 1][j] + 1, table[i][j - 1] + 1, table[i - 1][j - 1] + diag)

	return table[-1][-1]


def d_l_distance_recursion(str_1, str_2):
	if len(str_1) == 0:
		return len(str_2)

	elif len(str_2) == 0:
		return len(str_1)

	elif len(str_1) > 1 and len(str_2) > 1 and str_1[-1] == str_2[-2] and str_1[-2] == str_2[-1]:
		if str_1[-1] == str_2[-1]:
			diag = 0
		else:
			diag = 1

		d = min(d_l_distance_recursion(str_1, str_2[:-1]) + 1,
			d_l_distance_recursion(str_1[:-1], str_2) + 1,
			d_l_distance_recursion(str_1[:-1], str_2[:-1]) + diag,
			d_l_distance_recursion(str_1[:-2], str_2[:-2]) + 1)

		return d

	else:
		if str_1[-1] == str_2[-1]:
			diag = 0
		else:
			diag = 1

		d = min(d_l_distance_recursion(str_1, str_2[:-1]) + 1,
			d_l_distance_recursion(str_1[:-1], str_2) + 1,
			d_l_distance_recursion(str_1[:-1], str_2[:-1]) + diag)

		return d
