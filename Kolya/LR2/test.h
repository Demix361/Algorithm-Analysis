#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrio.h"
#include "memory.h"
#include "matrproc.h"
#include "errors.h"

#define TEST_NUM 6

int test_read_not_existing_or_empty_file();
int compare_matrix(double **matr1, double **matr2, int n1, int m1, int n2, int m2);
int test_addiction_multiple(int flag);
int test_determinant(int flag);

