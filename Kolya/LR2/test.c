#include "test.h"
#include <stdlib.h>
#include <time.h>

int range[6] = {10, 11, 200, 201, 1000, 1001};


unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}


void fillMatrix(double **matr, int n, int m)
{
    srand ( time(NULL) );
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matr[i][j] = rand() % 100 + 1;
        }
    }
}


int main()
{
	unsigned long long t1;
	double **matr1, **matr2;
	FILE *f = fopen("standart.txt", "w");
	FILE *f1 = fopen("vinograd.txt", "w");
	FILE *f2 = fopen("optimized.txt", "w");	

	for(int i = 0; i < 6; i++)
	{	
		matr1 = allocate_matrix(range[i], range[i]);
		matr2 = allocate_matrix(range[i], range[i]);
		fillMatrix(matr1, range[i], range[i]);
		fillMatrix(matr2, range[i], range[i]);		
		t1 = tick();
		multiple_matrix(matr1, matr2, range[i], range[i], range[i]);
		t1 -= tick();
		fprintf(f, "%d\t%lld\n", i, t1);
		free_matrix(matr1);
	}
	fclose(f);
	for(int i = 0; i < 6; i++)
	{	
		matr1 = allocate_matrix(range[i], range[i]);
		matr2 = allocate_matrix(range[i], range[i]);
		fillMatrix(matr1, range[i], range[i]);
		fillMatrix(matr2, range[i], range[i]);	
		t1 = tick();
		vinograd(matr1, matr2, range[i], range[i], range[i]);
		t1 -= tick();
		fprintf(f1, "%d\t%lld\n", i, t1);
		free_matrix(matr1);
	}
	fclose(f1);
	for(int i = 0; i < 6; i++)
	{	
		matr1 = allocate_matrix(range[i], range[i]);
		matr2 = allocate_matrix(range[i], range[i]);
		fillMatrix(matr1, range[i], range[i]);
		fillMatrix(matr2, range[i], range[i]);	
		t1 = tick();
		vinograd_optimized(matr1, matr2, range[i], range[i], range[i]);
		t1 -= tick();
		fprintf(f2, "%d\t%lld\n", i, t1);
		free_matrix(matr1);
	}
	fclose(f2);
	return 0;
}

int test_addiction_multiple(int flag)
{
	enum error code = 0;
	int n, m;
	FILE *f1 = fopen("test_1.txt", "r");
	FILE *f2 = fopen("test_2.txt", "r");
	FILE *fres;
	if(flag)
		fres = fopen("test_adiction_res.txt", "r");
	else
		fres = fopen("test_multiple_res.txt", "r");
	double **matr1 = readfile(f1, &n, &m);
	double **matr2 = readfile(f2, &n, &m);
	double **matr3 = readfile(fres, &n, &m);

	double **matrres = NULL;

	matrres = multiple_matrix(matr1, matr2, 2, 2, 2);
	code = compare_matrix(matrres, matr3, 2, 2, 2, 2);
	return code;
}

/*
Проверяет совпадение двух матриц

@param matr1 - матрица
@param matr2 - матрица
@param n1, m1 - размер матрицы 1
@param n2, m2 - размер матрицы 2

@return - код ошибки
*/
int compare_matrix(double **matr1, double **matr2, int n1, int m1, int n2, int m2)
{
	enum error code = 0;
	if(n1 != m1 || n2 != m2)
		code = TEST_ERROR;
	else
	{
		for(int i = 0; i < n1; i++)
		{
			for(int j = 0; j < n2; j++)
			{
				if(matr1[i][j] != matr2[i][j])
					code = TEST_ERROR;
			}
		}
	}
	return code;
}

