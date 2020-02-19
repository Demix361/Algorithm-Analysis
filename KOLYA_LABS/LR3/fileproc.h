#ifndef fileproc_h
#define fileproc_h

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

int readfile(FILE * f, int ** arr, int * np, int ** plast);
void writefile(FILE * f, int * base, int * plast);

#endif



