#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileproc.h"
#include "mysort.h"
#include "filter.h"
#include "printarr.h"
#include "errors.h"


#define TEST_NUM 4

int comparearray(int * pb1, int * pe1, int * pb2, int * pe2);
int keytest1();
int keytest2();
int mysorttest1();
int mysorttest2();
int readfiletest1();

int main()
{
	int errsum = 0;
	if(keytest1())
		printf("Key test 1 is not okay\n");
	else
		printf("Key test 1 is okay\n");
	if(keytest2())
		printf("Key test 2 is not okay\n");
	else
		printf("Key test 2 is okay\n");
	if(mysorttest1())
		printf("Sort test 1 is not okay\n");
	else
		printf("Sort test 1 is okay\n");
	if(mysorttest2())
		printf("Sort test 2 is not okay\n");
	else
		printf("Sort test 2 is okay\n");
	return errsum;
}


/**
Сравнивает 2 массива: pb1 и pb2

@param pb1 - первый массив
@param pe1 - указатель на конец первого массива
@param pb2 - второй массив
@param pe2 - указатель на конец второго массива

@return возвращает переменную code, 
которая равна 0 при совпадении массивов
и 1 при их несовпадении
*/

int comparearray(int * pb1, int * pe1, int * pb2, int * pe2)
{
	int code = 0;
	if (pe1 - pb1 != pe2 - pb2)
		code = -1;
	int * pcur1 = pb1;
	int * pcur2 = pb2;
	if (!code)
	{
		for (; pcur1 < pe1; pcur1++, pcur2++)
		{
			if (*pcur1 != *pcur2)
				code = -2;
		}
	}
	return code;
}

int keytest1()
{
	int * arr1 = NULL;
	int * plast1;
	int * arrtest1;
	int * plasttest1;
	int code = 0, err = 0;
	FILE *f = fopen("in_3.txt", "r");
	int n;
	readfile(f, &arr1, &n, &plast1);
	
	key(arr1, plast1, &arrtest1, &plasttest1);
	err = comparearray(arr1, plast1, arrtest1, plasttest1);
	if (err)
		code = -1;

	return code;
}

int keytest2()
{
	int * arr2;
	int *plast2;
	int * arrres2;
	int code = 0;
	enum error err = 0;
	int * arrtest2;
	int * plasttest2;
	int * plastres2;
	int n1;
	FILE *f1 = fopen("in_1.txt", "r");
	FILE *f2 = fopen("out_1.txt", "r");
	readfile(f1, &arr2, &n1, &plast2);
	readfile(f2, &arrres2, &n1, &plastres2);
	
	key(arr2, plast2, &arrtest2, &plasttest2);		
	err = comparearray(arrres2, plastres2, arrtest2, plasttest2);
	if (err)
		code = -1;
	return code;
}

int mysorttest1()
{
	int code = 0;
	enum error err = 0;
	int * arr4;
	int * plast4;
	int * arrres4;
	int * plastres4;
	FILE *f1 = fopen("in_2.txt", "r");
	FILE *f2 = fopen("out_5.txt", "r");
	int n1;
	readfile(f1, &arr4, &n1, &plast4);
	readfile(f2, &arrres4, &n1, &plastres4);

	mysort(arr4, plast4 - arr4, sizeof(int), compint);
	err = comparearray(arr4, plast4, arrres4, plastres4);
	if (err)
		code = -1;
	return code;
}

int mysorttest2()
{
	int code = 0;
	enum error err = 0;
	int * arr5;
	int * plast5;
	int * arrres5;
	int * plastres5;
	FILE *f1 = fopen("in_4.txt", "r");
	FILE *f2 = fopen("out_4.txt", "r");
	int n1;
	readfile(f1, &arr5, &n1, &plast5);
	readfile(f2, &arrres5, &n1, &plastres5);
			
	mysort(arr5, plast5 - arr5, sizeof(int), compint);		
	err = comparearray(arr5, plast5, arrres5, plastres5);
	if (err)
		code = -1;
	return code;
}
