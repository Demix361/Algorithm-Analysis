from main import lev_table, dam_lev_table, dam_lev_recursion
import ctypes, os
from time import time


def get_args(line):
	arr = line[:-1].split(",")

	return arr


class _tick():
	def __init__(self):
		self.value = time()


def time_test(str_1, str_2, amount):
	t1 = _tick()
	for i in range(amount):
		res= lev_table(str_1, str_2)
	t2 = _tick()
	t_lev_tab = (t2.value - t1.value) / amount
	
	t1 = _tick()
	for i in range(amount):    
		res = dam_lev_table(str_1, str_2)
	t2 = _tick()
	t_dam_lev_tab = (t2.value - t1.value) / amount
	
	t1 = _tick()
	for i in range(amount):
		res = dam_lev_recursion(str_1, str_2)
	t2 = _tick()
	t_dam_lev_rec = (t2.value - t1.value) / amount
	
	return t_lev_tab, t_dam_lev_tab, t_dam_lev_rec
	

def main(N):
	"""
	d = os.path.abspath(os.path.dirname(__file__))
	d += "/libtick.so"
	lib = ctypes.CDLL(d)

	_tick = lib.tick
	_tick = ctypes.c_ulonglong

	CLOCKS_PER_SEC = 2.2e+6
	"""
	with open("time_test.txt", "r") as f:
		for line in f:
			str_1, str_2 = get_args(line)
			length = len(str_1)
			t_lev_tab, t_dam_lev_tab, t_dam_lev_rec = time_test(str_1, str_2, N)

			print("Длина слова: ", length, "\nВремя итерационного Левенштейна: ", t_lev_tab, 
				"\nВремя итерационного Дамерау-Левенштейна: ", t_dam_lev_tab, 
				"\nВремя рекурсионного Дамерау-Левенштейна: ", t_dam_lev_rec, "\n", sep="")


if __name__ == "__main__":
	main(1000)

