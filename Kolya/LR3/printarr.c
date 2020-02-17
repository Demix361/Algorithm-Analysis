#include "printarr.h"

void printarr(int * pst, int * plast)
{
	for(int * pcur = pst; pcur < plast; pcur++)
		printf("%d ", *pcur);
	printf("\n");
}
