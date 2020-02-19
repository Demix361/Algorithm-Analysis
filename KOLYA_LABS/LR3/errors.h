#ifndef errors_h
#define errors_h

#include <stdio.h>

enum error
{
	POINTER_ERROR = -1, 
	NULL_ARRAY_SIZE = -2,
	MEMORY_ERROR = -3,
	FILE_NOT_FOUND = -4
};

void printerr(enum error code);

#endif
