#include "matrio.h"

/*
Считывание матрицы из файла

@param f - исходный файл
@paaram  n,m - размер матрицы

@return - возвращает считанную матрицу
*/

double **readfile(FILE *f, int *n, int *m)
{
	double **matr = NULL;
	if (f != NULL && !feof(f))
	{
		fscanf(f,"%d %d", n, m);
		matr = allocate_matrix(*n, *m);
		if(matr)
		{
			for(int i = 0; i < *n; i++)
			{
				for(int ii = 0; ii < *m; ii++)
					fscanf(f, "%lf", &matr[i][ii]);
			}
		}
	}
	return matr;
}

/*
Выводит матрицу на экран

@param matr - матрица
@param n, m - размеры матрицы
*/
void printmatr(double **matr, int n, int m)
{
	printf("\n");
	for(int i = 0; i < n; i++)
	{
		for(int ii = 0; ii < m; ii++)
			printf("%lf ", matr[i][ii]);
		printf("\n");
	}
	if ((n < 1) || (m < 1))
		printf("Empty matrix");
	printf("\n\n");
}

/*
Запись матрицы в файл

@param f - файл для записи
@param matr - исходная матрица
@paaram  n,m - размер матрицы

*/
void writefile(FILE *f,  double **matr, int n, int m)
{
	fprintf(f,"%d %d\n", n, m);
	for(int i = 0; i < n; i++)
	{
		for(int ii = 0; ii < m; ii++)
			fprintf(f, "%lf ", matr[i][ii]);
		fprintf(f,"\n");
	}
}

