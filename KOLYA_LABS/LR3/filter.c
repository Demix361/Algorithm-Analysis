#include "filter.h"

/**
Копирует элементы массива pb_src в массив pb_dst.

@param pb_src первый массив
@param pe_src указатель на конец первого массива
@param pb_dst второй массив
@param pe_dst указатель на конец второго массива

@return Возвращает 0, если ошибок не было, либо code, если переданы неверные параметры.
*/

int copyarray ( int *pb_src,  int *pe_src, int *pb_dst, int *pe_dst)
{
	int n = pe_src - pb_src;
	int * pcur1 = pb_src;
	enum error code = 0;
		
	if (n < 0)
		code = POINTER_ERROR;
	else if (n == 0)
		code = NULL_ARRAY_SIZE;	

	if (!code)
	{	
		int * pcur2 = pb_dst;
		for (;pcur1 < pe_src; pcur1++, pcur2++)
			*pcur2 = *pcur1;
	}
	
	return code;
}

/**
Создает новый массив, копирует в него все элементы исходного

@param pb_src первый массив
@param pe_src указатель на конец первого массива
@param pb_dst указатель на второй массив
@param pe_dst указатель на указатель на конец второго массива

@return Возвращает 0, если ошибок не было, либо code, если переданы неверные параметры.
*/

int getnewarray (int *pb_src,  int *pe_src, int **pb_dst, int **pe_dst)
{
	enum error code = 0;
	int n = pe_src - pb_src;
	
	if (n < 0)
		code = POINTER_ERROR;
	else if (n == 0)
		code = NULL_ARRAY_SIZE;
	else
		*pb_dst = (int *) malloc(n * sizeof(int));
	
	if (!code && *pb_dst)
	{
		*pe_dst = *pb_dst + n;
		copyarray(pb_src, pe_src, *pb_dst, *pe_dst);
	}
	else if (!code)
		code = MEMORY_ERROR;
		
	return code;
}

/**
Копирует элементы старого массива в новый


@param pb_src первый массив
@param pe_src указатель на конец первого массива
@param pb_dst указатель на второй массив
@param pe_dst указатель на указатель на конец второго массива

@return Возвращает 0, если ошибок не было, либо code, если переданы неверные параметры.
*/

int key( int *pb_src,  int *pe_src, int **pb_dst, int **pe_dst)
{
	enum error code = 0;
	int n = 0;
	int * pneg = pe_src;
	
	for (int * pcur = pb_src; pcur < pe_src; pcur++)
	{
		if (*pcur < 0)
		{
			pneg = pcur;
		}
	}
	
	n = pneg - pb_src;
	pe_src = pb_src + n;
	code = getnewarray(pb_src, pe_src, pb_dst, pe_dst);	
	
	return code;

}
