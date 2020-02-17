#include "errors.h"

/**
Выводит сообщение о коде ошибки

@param code код ошибки
*/

void printerr(enum error code)
{
	switch(code)
	{
		case WRONG_COMMAND_LINE_ARGUMENTS :
			printf("WRONG_COMMAND_LINE_ARGUMENTS \n");
			break;
		case MATRIX_READ_ERROR:
			printf("MATRIX_READ_ERROR\n");
			break;
		case MEMORY_ERROR:
			printf("MEMORY_ERROR \n");
			break;
		case WRONG_MATRIX_SIZE:
			printf("WRONG_MATRIX_SIZE \n");
			break;
		case TEST_ERROR:
			printf("TEST_ERROR \n");
			break;
	}
}
