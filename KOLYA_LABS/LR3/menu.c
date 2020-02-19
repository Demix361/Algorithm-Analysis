#include "menu.h"

/**
Подсчет времени сортировки

@param arrbew - массив 
@param plastnew - указатель на конец массива
@param tbarr - массив времен сортировки 
@param flag - флаг, указывающий, как сортировать


*/

void counttime(int * arrnew, int * plastnew, unsigned long long * tbarr, int flag)
{
	unsigned long long *ptimecur = tbarr;
	unsigned long long tb, te;
	unsigned long long *tblast = tbarr + COUNT_NUM;
	int *arrtmp = NULL, *plasttmp = NULL;
	
	for(;ptimecur < tblast; ptimecur++)
	{
		getnewarray(arrnew, plastnew, &arrtmp, &plasttmp);
		tb = tick();
		if (flag)
			mysort(arrtmp, plasttmp - arrtmp, sizeof(int), compint);
		else
			qsort(arrtmp, plasttmp - arrtmp, sizeof(int), compint);
		te = tick();
		*ptimecur = te - tb;
		printf("\tsort time: %llu\n", te - tb);
	}
}

/**
Подсчет времени сортировок

@param arrbew - массив 
@param plastnew - указатель на конец массива  

*/
void countsorttime(int * arrnew, int * plastnew)
{
	unsigned long long timems[COUNT_NUM];
	unsigned long long timeqs[COUNT_NUM];

	printf("Mysort times: \n");
	counttime(arrnew, plastnew, timems, 1);
	printf("Qsort times: \n");
	counttime(arrnew, plastnew, timeqs, 0);
}

/**
Отсчет кол-ва тактов процессора

@return d - количество тактов процессора
*/
unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}


/**
Фильтрация массива или копирование в новый, в зависимости от параметров командной строки

@param arr - начальный массив 
@param plast - указатель на конец начального массива 
@param arrnew - получившийся массив 
@param plastnew - указатель на конец получившегося массива 
@param argc - количество параметров командной строки
@param arv - значение параметров командной строки 

@return Возвращает 0, если ошибок не было, либо code, если переданы неверные параметры.
*/
int arrproc(int * arr, int * plast, int ** arrnew, int ** plastnew, int argc, char * argv[])
{
	printf("array after reading file: ");
	printarr(arr, plast);
	enum error code = 0;
	
	if ((argc == 4) && (strcmp(argv[3], "f") == 0))
	{
		code = key(arr, plast, arrnew, plastnew);
		if (!code)
		{
			printf("array after fitlering: ");
			printarr(*arrnew, *plastnew);
		}
	}
	else
		code = getnewarray(arr, plast, arrnew, plastnew);
	return code;
}
