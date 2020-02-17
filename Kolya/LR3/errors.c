#include "errors.h"

/**
Выводит сообщение о коде ошибки

@param code код ошибки
*/

void printerr(enum error code)
{
	switch(code)
	{
		case POINTER_ERROR:
			printf("Pointer error.\n");
			break;
		case NULL_ARRAY_SIZE:
			printf("Empty array after filtering.\n");
			break;
		case MEMORY_ERROR:
			printf("Memory error.\n");
			break;
		case FILE_NOT_FOUND:
			printf("File not found\n");
			break;
	}
}
