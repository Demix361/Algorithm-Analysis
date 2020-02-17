#ifndef matrio_h
#define matrio_h

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "memory.h"

double **readfile(FILE *f, int *n, int *m);
void printmatr(double **matr, int n, int m);
void writefile(FILE *f,  double **matr, int n, int m);

#endif
