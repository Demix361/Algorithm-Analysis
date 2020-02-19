#include "fileproc.h"

/**
Функция записи массива в файл.

@param f - файл для записи
@param base - указатель на начало массива
@param plast - указатель на конец массива
*/

void writefile(FILE * f, int * base, int * plast)
{
	for(int * pcur = base; pcur < plast; pcur++)
	{
		fprintf(f, "%d ", *pcur);
	}
}

/**
Функция считывания файла в массив.

@param f - файл для чтения
@param arr - указатель на массив
@param np - указатель на кол-во элементов
@param plast - указатель на указатель на конец массива

@return возвращает код ошибки
*/
int readfile(FILE * f, int ** arr, int * np, int ** plast)
{
	int a;
	*np = 0;
	enum error code = 0;
	
	if (feof(f))
		code = FILE_NOT_FOUND;

	if  (!code)
	{		
		while (fscanf(f, "%d", &a) == 1)
			(*np)++;
	
		*arr = (int *) malloc ((*np) * sizeof(int));
		if (*arr)
		{
			
			*plast = *arr + *np;
			fseek(f, 0, SEEK_SET);
			for (int * pcur = *arr; pcur < *plast; pcur++)
			{
				fscanf(f, "%d", pcur);
			}
		}
		else
			code = MEMORY_ERROR;
	}
	return code;
}
