#ifndef errors_h
#define errors_h

#include <stdio.h>

enum error
{
	WRONG_COMMAND_LINE_ARGUMENTS = -1,
	MATRIX_READ_ERROR = -2,
	MEMORY_ERROR = -3,
	WRONG_MATRIX_SIZE = -4,
	TEST_ERROR = -5
};

void printerr(enum error code);

#endif
