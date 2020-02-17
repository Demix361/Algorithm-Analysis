#ifndef mysort_h
#define mysort_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compint(const void * x1, const void * x2);
void intswap(void * p1, void *p2, size_t size);
void mysort(void * base, int n, size_t size, int (*compare) (const void *, const void *));

#endif
