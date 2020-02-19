#include "main.h"
#include <stdlib.h>
#include <time.h>

void bubblesort(int * arr, int n);
void bubblebar(int *arr, int n);
void shakersort(int *arr, int n);

int *generate(int n, int flag)
{
	int * res = (int *)calloc(n, sizeof(int));
	for(int i = 0; i < n; i++)
	{
		if (flag == 0)
		{
			srand(time(NULL));
			res[i] = rand();
		}
		else if(flag == 1)
			res[i] = i;
		else
			res[i] = n - i;
	}
	return res;
}

int main()
{
	FILE *r_b = fopen("r_b.txt","w");
	FILE *r_b_b = fopen("r_b_b.txt","w");
	FILE *r_s = fopen("r_s.txt","w");
	FILE *s_b = fopen("s_b.txt","w");
	FILE *s_b_b = fopen("s_b_b.txt","w");
	FILE *s_s = fopen("s_s.txt","w");
	FILE *sr_b = fopen("sr_b.txt","w");
	FILE *sr_b_b = fopen("sr_b_b.txt","w");
	FILE *sr_s = fopen("sr_s.txt","w");
	for(int i = 100; i <= 1500; i += 100)
	{
		int *arr = generate(i, 0);
		int t1 = tick();
		for(int j = 0; j < 100; j++)
			bubblesort(arr, i);
		int t2 = (tick() - t1);
		fprintf(r_b, "%d %d\n", i, t2);
		
		free(arr);	
		arr = generate(i, 0);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			bubblebar(arr, i);
		t2 = (tick() - t1);
		fprintf(r_b_b, "%d %d\n", i, t2);
		
		free(arr);
		arr = generate(i, 0);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			shakersort(arr, i);
		t2 = (tick() - t1);
		fprintf(r_s, "%d %d\n", i, t2);

		free(arr);
		arr = generate(i, 1);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			bubblesort(arr, i);
		t2 = (tick() - t1);
		fprintf(s_b, "%d %d\n", i, t2);
		
		free(arr);
		arr = generate(i, 1);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			bubblebar(arr, i);
		t2 = (tick() - t1);
		fprintf(s_b_b, "%d %d\n", i, t2);
		
		free(arr);
		arr = generate(i, 1);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			shakersort(arr, i);
		t2 = (tick() - t1);
		fprintf(s_s, "%d %d\n", i, t2);

		free(arr);
		arr = generate(i, 2);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			bubblesort(arr, i);
		t2 = (tick() - t1);
		fprintf(sr_b, "%d %d\n", i, t2);
		
		free(arr);
		arr = generate(i, 2);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			bubblebar(arr, i);
		t2 = (tick() - t1);
		fprintf(sr_b_b, "%d %d\n", i, t2);
		
		free(arr);
		arr = generate(i, 2);
		t1 = tick();
		for(int j = 0; j < 100; j++)
			shakersort(arr, i);
		t2 = (tick() - t1);
		fprintf(sr_s, "%d %d\n", i, t2);		
	}
}
