#include "memory.h"

/*
Выделяет память под матрицу

@param n, m - размеры матрицы

@return - возвращает матрицу с выделенной памятью
*/
double **allocate_matrix(int n, int m)
{
	double **matr = malloc(n * sizeof(double *) + n*m*sizeof(double));
	if (matr)
	{
		for(int i = 0; i < n; i++)
			matr[i] = (double *)((char*) matr + n * sizeof(double*) + i * m * sizeof(double));
	}
	else
		matr = NULL;
	return matr;
}

/*
Освобождает память под матрицу

@param matr - матрица
*/
void free_matrix(double **matr)
{
    if(matr)
	    free(matr);
}
