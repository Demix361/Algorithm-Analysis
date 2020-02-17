#include "matrproc.h"

/*
Сложение двух матриц

@param matr1, matr2 - исходные матрицы
@param n, m - размеры матриц

@return возвращает результирующую матрицу
*/
double **addiction_matrix(double **matr1, double **matr2, int n, int m)
{
	double **matrres = NULL;
	matrres = allocate_matrix(n,m);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			matrres[i][j] = matr1[i][j] + matr2[i][j];
	}
	return matrres;
}

double *allocate_array(int n)
{
	double *newarr = (double *)calloc(n, sizeof(double));
	return newarr;
}

/*
Умножение двух матриц

@param matr1, matr2 - исходные матрицы
@param n, m - размеры матриц

@return возвращает результирующую матрицу
*/
double **multiple_matrix(double **matr1, double **matr2, int n, int m, int m1)
{
	double **matrres = NULL;
	matrres = allocate_matrix(n,m);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			matrres[i][j] = 0;
			for(int k = 0; k < m1; k++)
				matrres[i][j] += matr1[i][k] * matr2[k][j];
		}
	}
	return matrres;
}

double **vinograd(double **matr1, double **matr2, int n, int m, int m1)
{
	double *mulh = allocate_array(n);
	double *mulv = allocate_array(m);
	
	double **matrres = allocate_matrix(n, m);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m1/2; j++)
			mulh[i] = mulh[i] + matr1[i][2*j] * matr1[i][2*j + 1];

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m1/2; j++)
			mulv[i] = mulv[i] + matr2[2*j][i] * matr2[2*j + 1][i];
			
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			matrres[i][j] = - mulh[i] - mulv[j];
			for (int k = 0; k < m1/2; k++)
				matrres[i][j] = matrres[i][j] + (matr1[i][2*k]+matr2[2*k+1][j])*(matr1[i][2*k+1]+matr2[2*k][j]);
		}
	}
	
	if (m1 % 2)
	{
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				matrres[i][j] = matrres[i][j] + matr1[i][m1 - 1] * matr2[m1 - 1][j];
	}
	return matrres;
}

double **vinograd_optimized(double **matr1, double **matr2, int n, int m, int m1)
{
	double *mulh = allocate_array(n);
	double *mulv = allocate_array(m);
	
	double **matrres = allocate_matrix(n, m);
    _Bool flag = m1 % 2;
    int N = m1 - 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m1 - flag; j += 2)
            mulh[i] += matr1[i][j] * matr1[i][j + 1];
            
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m1 - flag; j += 2)
            mulv[i] += matr2[j][i] * matr2[j + 1][i];
            

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrres[i][j] -= mulh[i] + mulv[j];
            for (int k = 0; k < m1 - flag; k += 2)
                matrres[i][j] +=(matr1[i][k] + matr2[k + 1][j]) * (matr1[i][k + 1] + matr2[k][j]);
        }
    }
    
    if (flag)    
    {
    	for (int i = 0; i < n; i++)
    	    for (int j = 0; j < m; j++)
    		    matrres[i][j] += matr1[i][N] * matr2[N][j];
    }
    return matrres;
}

/*
Копирование исходной матрицы в новую, за исключением заданной строки и первого столбца

@param matr_src - исходная матрица
@param matr_res - результирующая матрица
@param stringindex - индекс строки, которую надо пропустить при копировании
@param n - количество строк/столбцов результирующей матрицы
*/
void copy_column_matrix(double **matr_src, double **matr_res, int stringindex, int n)
{
	for(int i = 0; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(i != stringindex)
			{
				matr_res[i - (i > stringindex)][j - 1] = matr_src[i][j];
			}
		}
	}
}

/*
Вычисление определителя методом первого столбца

@param matr_src - исходная матрица
@param n - ее размер
@param determinant - указатель на определитель

@return - возвращает код ошибки
*/
int determinant_column(double **matr_src, int n, double *determinant)
{
	enum error code = 0;
	double det = 0;
	if(!code && n <= 2)
		*determinant += matr_src[0][0]*matr_src[1][1] - matr_src[0][1]*matr_src[1][0];
	else if (!code)
	{
		for(int i = 0; i < n; i++)
		{
			double **matr = NULL;
			int sign = pow(-1, i);
			matr = allocate_matrix(n - 1, n - 1);
			if(matr)
			{
				copy_column_matrix(matr_src, matr, i, n - 1);
				det = 0;
				determinant_column(matr, n - 1, &det);
				*determinant += sign * matr_src[i][0] * det;
				free_matrix(matr);
			}
			else
				code = MEMORY_ERROR;
		}
	}
	return code;
}
