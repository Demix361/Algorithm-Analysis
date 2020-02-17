#include "mysort.h"

/**
Функция сравнения двух чисел типа int.

@param x1 - указатель на первое число
@param x2 - указатель на второе число

@return возвращает разность первого и второго числа
*/

int compint(const void * x1, const void * x2)
{
	return ( *(int*)x1 - *(int*)x2 );
}

/**
Меняет значения из первого и второго указателей

@param p1 - первый указатель
@param p2 - второй указатель
*/
void intswap(void * p1, void *p2, size_t size)
{
	void *tmp = malloc(size);
	memcpy(tmp, p1, size);
	memcpy(p1, p2, size);
	memcpy(p2, tmp, size);
	free(tmp);
}


/**
Пробег по массиву, по сути - сортировка пузырьком.

@param pright - указатель на начало массива
@param pleft - указатель на начало массива
@param compare - функция сравнения
*/
void runarray(void * pright, void * pleft, size_t size, int (*compare) (const void *, const void *), char ** barrier, int flag)
{
	char * pcur;
	if (flag)
		pcur = (char *)pright;
	else
		pcur = (char *)pleft + size;
		
	for(; pcur <= (char *)pright && pcur > (char *)pleft;)
	{
		if(compare((pcur - size), pcur) > 0)
		{
			intswap(pcur - size,pcur, size);
			if (flag)
				*barrier = pcur - size;
			else
				*barrier = pcur;
		}
		if (flag)
			pcur -= size;
		else
			pcur += size;
	}

}

void bubblesort(int * arr, int n)
{
	int tmp;
	for(int i = 0; i < n; i++)	
	{
		for(int j = 0; j < n - 1 - i; j++)
		{
			if(arr[j] > arr[j + 1])
			{
				tmp = arr[j] ;
				arr[j] = arr[j + 1] ;
				arr[j + 1] = tmp;
			}
		}
	}
}


void bubblebar(int *arr, int n)
{
    int tmp;
    int barrier;
    do 
    {
        barrier = 0;
        for (int i = 0; i < n - 1; i++) 
        {
            if (arr[i] > arr[i + 1]) 
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                barrier = i + 1;
            }
        }
        n = barrier;
    } while (n != 0);
}



void shakersort(int *arr, int n)
{
	int left = 0, right = n - 1, barrier = 0, tmp = 0;
	do
	{
		barrier = left;
		for(int i = left; i < right; i++)
		{
            if (arr[i] > arr[i + 1]) 
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                barrier = i;
            }
		}
		right = barrier;
		
		barrier = right;
		for(int i = right; i > left; i--)
		{
            if (arr[i] < arr[i - 1]) 
            {
                tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;               
                barrier = i - 1;
            }
		}
		left = barrier;		
	}
	while(left != right);	
}
/**
Шейкер - сортировка

@param base  массив
@param plast указатель на конец массива
@param size размер переменных в байтах
@param compare - указатель на функцию сравнения двух элементов
*/

void mysort(void * base, int n, size_t size, int (*compare) (const void *, const void *))
{
	char * pleft = base;
	char * pright = (char *)base + (n - 1) * size;
	char * barrier = (char *)base;
	do
	{
		runarray(pright, pleft, size, compare, &barrier, 1);
		pleft = barrier + size;
		runarray(pright, pleft, size, compare, &barrier, 0);
		pright = barrier - size;

	} while(pleft < pright);
	return;
}
