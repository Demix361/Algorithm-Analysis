#include "main.h"

int main()
{
	double **matr1 = NULL, **matr2 = NULL, **matrres = NULL;
	int n1 = 0, m1 = 0, n2 = 0, m2 = 0, n = 0, m = 0;
	char fname1[100], fname2[100];
	printf("Input filename of first matrix: ");
	scanf("%s", fname1);
		
	FILE *f1 = fopen(fname1, "r");
	enum error code = 0;

	matr1 = readfile(f1, &n1, &m1);
	if (matr1)
	{
		printf("Matrix 1:\n");
		printmatr(matr1, n1, m1);
	}
	
	printf("Input filename of second matrix: ");
	scanf("%s", fname2);
	FILE *f2 = fopen(fname2, "r");

	matr2 = readfile(f2, &n2, &m2);
	if (matr2)
	{
		printf("Matrix 2:\n");
		printmatr(matr2, n2, m2);
	}
	if (!matr1 || !matr2)
		code = MATRIX_READ_ERROR;
	else if (m1 != n2)
		code = WRONG_MATRIX_SIZE;

	n = n1;
	m = m2;
	
	if (!code)
	{
		matrres = multiple_matrix(matr1, matr2, n1, m2, m1);
		printf("Result matrix(standart):\n");
		printmatr(matrres, n, m);
		matrres = vinograd(matr1, matr2, n1, m2, m1);
		printf("Result matrix(vinograd):\n");
		printmatr(matrres, n, m);
		matrres = vinograd_optimized(matr1, matr2, n1, m2, m1);
		printf("Result matrix(vinograd optimized):\n");
		printmatr(matrres, n, m);
		free_matrix(matr1);
		free_matrix(matr2);
		free_matrix(matrres);
	}
	printerr(code);
	return code;
}
