import random

def generate_matrix(m, n):
	matr = [[0 for i in range(m)] for j in range(n)]
	for i in range(n):
		for j in range(m):
			matr[i][j] = random.randint(1, 10)
	return matr

def put_matr_in_file(matr, f, m, n):
	f.write(str(n) + ' ' + str(m) + ' \n')
	for i in range(n):
		for j in range(n):
			f.write(str(matr[i][j]) + ' ')
		f.write('\n')

for i in range(10, 51, 10):
	matr = generate_matrix(i, i)
	f = open("matr_"+ str(i)+".txt","w")
	put_matr_in_file(matr, f, i, i)
	matr = generate_matrix(i + 1, i + 1)
	f = open("matr_"+ str(i + 1)+".txt","w")
	put_matr_in_file(matr, f, i + 1, i + 1)
