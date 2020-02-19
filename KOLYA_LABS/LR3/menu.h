#ifndef menu_h
#define menu_h

#define COUNT_NUM 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileproc.h"
#include "mysort.h"
#include "filter.h"
#include "printarr.h"
#include "errors.h"

void counttime(int * arrnew, int * plastnew, unsigned long long * tbarr, int flag);
void countsorttime(int * arrnew, int * plastnew);
unsigned long long tick(void);
int arrproc(int * arr, int * plast, int ** arrnew, int ** plastnew, int argc, char * argv[]);

#endif
