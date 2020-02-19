#ifndef matrproc_h
#define matrproc_h

#include <stdio.h>
#include <math.h>

#include "memory.h"
#include "matrio.h"
#include "errors.h"

double **addiction_matrix(double **matr1, double **matr2, int n, int m);
double **multiple_matrix(double **matr1, double **matr2, int n, int m, int m2);
int determinant_column(double **matr_src, int n, double *determinant);
double **getnewmatrix(double **matrsrc, int stringindex, int n);
double **vinograd(double **matr1, double **matr2, int n, int m, int m1);
double **vinograd_optimized(double **matr1, double **matr2, int n, int m, int m1);

#endif
