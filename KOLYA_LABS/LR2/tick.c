#include "main.h"

int main(void)
{
	int code = 0;
	int **matr = NULL, **vector = NULL, **result = NULL, **matr1 = NULL, **matr2 = NULL;
	int n, m, num, nv, mv = 1, numv, numres, n1, m1, n2, m2, num1, num2;
	int *A, *AV, *IA, *IAV;
	int *ARES, *IARES;
	first_in_line *JA = NULL, *JAV = NULL, *JARES = NULL;
	FILE *f, *fv;
	char input[100];
	char *fname;
	int flag = 0;
	
	printf("How do you want to input matrix and? 0 - read from file, 1 - in console: ");
	fgets(input, 100, stdin);
	
	if(!strcmp(input, "0\n"))
	{
		null_string(input, 99);
		printf("\nAvailable files for matrix:\n3x4 matrix: in_1.txt\n10x10 matrix: 10_5.txt, 10_10.txt, 10_20.txt\n100x100 matrix: 100_5.txt, 100_10.txt, 100_20.txt\n");
		printf("Input filename of matrix: \n");
		scanf("%s", input);
		f = fopen(input, "r");
		if(!f)
		{
			printf("Can`t open the file.\n");
			code = -1;
		}
		
		if(!code)
		{
			null_string(input, 99);
			printf("\nAvailable files for vector-column:\n4x1 vector: in_2.txt\n10x1 vector: vector10.txt\n100x1 vector: vector100.txt\n");
			printf("Input filename of vector-column: \n");
			scanf("%s", input);
			fv = fopen(input, "r");
			if(!fv)
			{
				printf("Can`t open the file.\n");
				code = -1;
			}
		}
		
		if(!code)
		{
			matr = readfile(f, matr, &n, &m, &num);
			vector = readfile(fv, vector, &nv, &mv, &numv);
			fclose(f);
			fclose(fv);
		}
		
	}
	else if(!strcmp(input, "1\n"))
	{
		printf("Input first matrix\n");
		matr = input_matrix(matr, &n, &m, &num);
		if(matr)
		{
			printf("Input vector\n");
			vector = input_matrix(vector, &nv, &mv, &numv);
			if(!vector)
				code = -1;
			if(nv <= 0 || mv <= 0)
				code = -1;
		}
		else
			code = -1;
		if(n <= 0 || m <= 0)
			code = -1;
	}
	else
	{
		printf("Wrong point\n");
		code = -1;
	}
	
	
	if(!code && mv != 1)
	{
		printf("Wrong input. Vector-column`s m should be 1\n");
		return -1;
	}
	if(!code)
		getchar();
	if(!code && matr && vector)
	{
		printf("\nInput 1 to print matrix or anything else to not to print\n");
		fgets(input, 100, stdin);
		if(!strcmp(input, "1\n"))
			printmatr(matr, n, m);
		A = (int *)malloc(num * sizeof(int));
		IA = (int *)malloc(num * sizeof(int));
		JA = make_sparse_matrix(matr, n, m, A, IA, JA);
		printf("Array of non-zero elements: \n");
		printarr(A, A + num);
		printf("Their string indexes: \n");
		printarr(IA, IA + num);
		printf("Pairs of index of start of column - column index:\n");
		print_list(JA);
		
		printf("\nInput 1 to print vector or anything else to not to print\n");
		fgets(input, 100, stdin);
		if(!strcmp(input, "1\n"))
			printmatr(vector, nv, mv);		
		AV = (int *)malloc(numv * sizeof(int));
		IAV = (int *)malloc(numv * sizeof(int));
		JAV = make_sparse_matrix(vector, nv, mv, AV, IAV, JAV);
		printf("Array of non-zero elements: \n");
		printarr(AV, AV + numv);
		printf("Their string indexes: \n");
		printarr(IAV, IAV + numv);
		printf("Pairs of index of start of column - column index:\n");
		print_list(JAV);
	}
	
		
	while(!code && !flag)	
	{		

		null_string(input, 99);
		printf("\nInput number of menu point you want to choose:\n0 - multiple matrix and vector-column by usual method\n1 - multiple matrix and vector-column by sparse method\n2 - compare effictivity\n3 - exit: \n");
		fgets(input, 100, stdin);
		if(!strcmp(input, "0\n"))
		{
			if(m == nv)
			{
				result = multiple_matrix(matr, vector, n, mv, nv);
				printf("\nResult matrix: \n");
				printmatr(result, n, mv);
			}
			else
			{
				printf("\nWrong sizes of matrix and vector, can`t multiple\n");
			}
		}
		
		else if(!strcmp(input, "1\n"))
		{
			JARES = multiple_sparse_matrix(A, AV, IA, IAV, num, JA, numv, &ARES, &IARES, &n, nv);
			if(n)
			{
				printf("\nArray of non-zero elements: \n");
				printarr(ARES, ARES + n);
				printf("Their string indexes: \n");
				printarr(IARES, IARES + n);
				printf("Pairs of index of start of column - column index:\n");
				print_list(JARES);
			}
			else
			{
				printf("Null matrix\n");
			}
		}
		else if(!strcmp(input, "2\n"))
		{
			compare_effictivity();
		}
		else if(!strcmp(input, "3\n"))
		{
			flag = 1;
		}
		else
			printf("Menu point not found. Please, try again\n");
	}
	if(!code)
	{
		free(A);
		free(IA);
		free(AV);
		free(IAV);
		free(ARES);
		free_matrix(matr);
		free_matrix(vector);
		free_matrix(result);
	}
	return 0;
}

void count_effictivity(FILE *f1, FILE *f2, unsigned long long *t_std, unsigned long long *t_spr, long long *mem_std, long long  *mem_sprs)
{
	int **matr1 = NULL, **matr2 = NULL, **matrres = NULL;
	int n1, m1, num1, n2, m2, num2;
	int *A1 = NULL, *A2 = NULL, *IA1 = NULL, *IA2 = NULL;
	int *ARES = NULL, *IARES = NULL;
	first_in_line *JA1 = NULL, *JA2 = NULL, *JARES = NULL;	
	
	*t_std = 0;
	*t_spr = 0;
	*mem_std = 0;
	*mem_sprs = 0;
	
	matr1 = readfile(f1, matr1, &n1, &m1, &num1);
	matr2 = readfile(f2, matr2, &n2, &m2, &num2);
	
	(*mem_std) += (n1 * m1 + n2 * m2 + n1 * m2) * sizeof(int);
	
	A1 = (int *)malloc(num1 * sizeof(int));
	IA1 = (int *)malloc(num1 * sizeof(int));
	JA1 = make_sparse_matrix(matr1, n1, m1, A1, IA1, JA1);	
	
	A2 = (int *)malloc(num2 * sizeof(int));
	IA2 = (int *)malloc(num2 * sizeof(int));
	JA2 = make_sparse_matrix(matr2, n2, m2, A2, IA2, JA2);
	
	(*mem_sprs) += (num1 * 2 + num2 * 2) * sizeof(int) + count_memory(JA1) + count_memory(JA2);
	
	(*t_std) -= tick();
	matrres = multiple_matrix(matr1, matr2, n1, m1, n2);
	(*t_std) += tick();

	(*t_spr) -= tick();
	JARES = multiple_sparse_matrix(A1, A2, IA1, IA2, num1, JA1, num2, &ARES, &IARES, &n1, n2);
	(*t_spr) +=  tick();
	
	free(matr1);
	free(matr2);
	free(matrres);
	free(A1);
	free(IA1);
	free(A2);
	free(IA2);
	fclose(f1);
	fclose(f2);
}

void compare_effictivity(void)
{
	FILE *f1 = NULL, *f2 = NULL;
	
	unsigned long long t_std = 0, t_sprs = 0;
	unsigned long long t1 = 0, t2 = 0;
	long long int mem_std = 0, mem_sprs = 0;
	
	f1 = fopen("10_5.txt", "r");
	f2 = fopen("vector10.txt", "r"); 
	count_effictivity(f1, f2, &t_std, &t_sprs, &mem_std, &mem_sprs);
	t1 = t_std;
	t2 = t_sprs;
	printf("\nTime for multiplication of 10x10 matrix with 5%% by standart and sparse methods (in clocks): %lld %lld\n", t1, t2);
	printf("Memory used by standart and sparse methods (in bytes): %lld %lld\n", mem_std, mem_sprs);
	printf("Advantage of sparse method(100%% - sparse method): %lf%% - time, %lf%% - memory\n\n", 100 * ((double)t1/(double)t2), 100 * ((double)mem_std/(double)mem_sprs));

	f1 = fopen("10_10.txt", "r");
	f2 = fopen("vector10.txt", "r");
	count_effictivity(f1, f2, &t_std, &t_sprs, &mem_std, &mem_sprs);
	t1 = t_std;
	t2 = t_sprs;
	printf("Time for multiplication of 10x10 matrix with 10%% by standart and sparse methods (in clocks): %lld %lld\n", t1, t2);
	printf("Memory used by standart and sparse methods (in bytes): %lld %lld\n", mem_std, mem_sprs);
	printf("Advantage of sparse method(100%% - sparse method): %lf%% - time, %lf%% - memory\n\n", 100 * ((double)t1/(double)t2), 100 * ((double)mem_std/(double)mem_sprs));

	f1 = fopen("10_20.txt", "r");
	f2 = fopen("vector10.txt", "r");
	count_effictivity(f1, f2, &t_std, &t_sprs, &mem_std, &mem_sprs);
	t1 = t_std;
	t2 = t_sprs;
	printf("Time for multiplication of 10x10 matrix with 10%% by standart and sparse methods (in clocks): %lld %lld\n", t1, t2);
	printf("Memory used by standart and sparse methods (in bytes): %lld %lld\n", mem_std, mem_sprs);
	printf("Advantage of sparse method(100%% - sparse method): %lf%% - time, %lf%% - memory\n\n", 100 * ((double)t1/(double)t2), 100 * ((double)mem_std/(double)mem_sprs));

	f1 = fopen("100_5.txt", "r");
	f2 = fopen("vector100.txt", "r"); 
	count_effictivity(f1, f2, &t_std, &t_sprs, &mem_std, &mem_sprs);
	t1 = t_std;
	t2 = t_sprs;
	printf("Time for multiplication of 100x100 matrix with 10%% by standart and sparse methods (in clocks): %lld %lld\n", t1, t2);
	printf("Memory used by standart and sparse methods (in bytes): %lld %lld\n", mem_std, mem_sprs);
	printf("Advantage of sparse method(100%% - sparse method): %lf%% - time, %lf%% - memory\n\n", 100 * ((double)t1/(double)t2), 100 * ((double)mem_std/(double)mem_sprs));
	
		
	f1 = fopen("100_10.txt", "r");
	f2 = fopen("vector100.txt", "r"); 
	count_effictivity(f1, f2, &t_std, &t_sprs, &mem_std, &mem_sprs);
	t1 = t_std;
	t2 = t_sprs;
	printf("Time for multiplication of 100x100 matrix with 10%% by standart and sparse methods (in clocks): %lld %lld\n", t1, t2);
	printf("Memory used by standart and sparse methods (in bytes): %lld %lld\n", mem_std, mem_sprs);
	printf("Advantage of sparse method(100%% - sparse method): %lf%% - time, %lf%% - memory\n\n", 100 * ((double)t1/(double)t2), 100 * ((double)mem_std/(double)mem_sprs));
		
	f1 = fopen("100_20.txt", "r");
	f2 = fopen("vector100.txt", "r"); 
	count_effictivity(f1, f2, &t_std, &t_sprs, &mem_std, &mem_sprs);
	t1 = t_std;
	t2 = t_sprs;
	printf("Time for multiplication of 100x100 matrix with 20%% by standart and sparse methods (in clocks): %lld %lld\n", t1, t2);
	printf("Memory used by standart and sparse methods (in bytes): %lld %lld\n", mem_std, mem_sprs);
	printf("Advantage of sparse method(100%% - sparse method): %lf%% - time, %lf%% - memory\n\n", 100 * ((double)t1/(double)t2), 100 * ((double)mem_std/(double)mem_sprs));
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}
