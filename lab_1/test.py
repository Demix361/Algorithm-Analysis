from random import randint
from time import time
from distances import *


def p(table):
	for i in range(len(table)):
		print(table[i])
	print()


def random_rus_str(length):
	abc = "укен" #"йцукенгшщзхъфывапролджэячсмитьбюё"
	res = ""

	for i in range(length):
		res += abc[randint(0, len(abc) - 1)]

	return res


def time_default_vs_transp(amount, length):
	a = random_rus_str(length)
	b = random_rus_str(length)
	beg = time()

	for i in range(amount):
		l_distance_table(a, b)

	l_time = (time() - beg) / amount

	beg = time()

	for i in range(amount):
		d_l_distance_table(a, b)

	d_l_time = (time() - beg) / amount

	print(a, b)
	print(l_time, d_l_time)

	return l_time, d_l_time


def time_table_vs_recursion(amount, length):
	a = random_rus_str(length)
	b = random_rus_str(length)
	beg = time()

	for i in range(amount):
		d_l_distance_table(a, b)

	tab_time = (time() - beg) / amount

	beg = time()

	for i in range(amount):
		d_l_distance_recursion(a, b)

	rec_time = (time() - beg) / amount

	print(a, b)
	print(tab_time, rec_time)

	return tab_time, rec_time



