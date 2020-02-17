#ifndef filter_h
#define filter_h

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

int key(int * pb_src, int * pe_src, int ** pb_dst, int ** pe_dst);
int copyarray ( int * pb_src,  int * pe_src, int * pb_dst, int * pe_dst);
int getnewarray (int *pb_src,  int *pe_src, int **pb_dst, int **pe_dst);

#endif
