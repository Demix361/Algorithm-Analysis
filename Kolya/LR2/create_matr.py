import random

def generate_matrix(m, n):
	matr = [[0 for i in range(m)] for j in range(n)]
	for i in range(n):
		for j in range(m):
			matr[i][j] = random.randint(10, 100)
	return matr

def put_matr_in_file(matr, f, m, n):
	f.write(str(n) + ' ' + str(m) + ' \n')
	for i in range(n):
		for j in range(n):
			f.write(str(matr[i][j]) + ' ')
		f.write('\n')

for i in range(3, 10):
	matr = generate_matrix(i, i)
	f = open("./BAUMANKA/5/AnAlg/LR6/matr_" + str(i) + "10.txt","w")
	put_matr_in_file(matr, f, i, i)
