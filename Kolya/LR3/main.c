#include "main.h"
void bubblesort(int * arr, int n);
void bubblebar(int *arr, int n);
void shakersort(int *arr, int n);

int main(int argc, char * argv[])
{
	FILE * infile = fopen(argv[1], "r");
	FILE * outfile = fopen(argv[2], "w");
	int * arr = NULL;
	enum error code = 0;
	int n;
	int * plast = NULL;
	int * arrbub = NULL;
	int * arrbubf = NULL;
	int * arrshak = NULL;
	int * plastbub = NULL;
	int * plastbubf = NULL;
	int * plastshak = NULL;
	
	if (infile == NULL || outfile == NULL)
		code = FILE_NOT_FOUND;

	if (!code)
		code = readfile(infile, &arr, &n, &plast);
		
	if (!code)
	{
		code = arrproc(arr, plast, &arrbub, &plastbub, argc, argv);
		code = arrproc(arr, plast, &arrbubf, &plastbubf, argc, argv);
		code = arrproc(arr, plast, &arrshak, &plastshak, argc, argv);
	}
	
	if(!code)
	{
		printarr(arrbub, plastbub);
	}
	
	
	if (!code)
	{
		printf("bubblesort: ");
		bubblesort(arrbub, n);
		printarr(arrbub, plastbub);
		printf("\nbubbleflag: ");
		bubblebar(arrbubf, n);
		printarr(arrbubf, plastbubf);
		printf("\nshakersort: ");
		shakersort(arrshak, n);
		printarr(arrshak, plastshak);
		code = 0;
		free(arrbub);
		free(arrbubf);
		free(arrshak);
	}
	
	printerr(code);
	return code;
}
