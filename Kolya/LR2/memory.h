#ifndef memory_h
#define memory_h

#include <stdio.h>
#include <stdlib.h>

double **allocate_matrix(int n, int m);
void free_matrix(double **matr);

#endif
