from time import time, sleep


class _tick():
	def __init__(self):
		self.value = time()

t1 = _tick()
sleep(2)
t2 = _tick()

print(t1.value, t2.value)