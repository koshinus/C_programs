#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
	int n;
	scanf ("%lf", &n);
	double *ar1;
	double *ar2;
	double *ar3;
	ar1 = (double *) malloc(sizeof(double) * n);
	ar2 = (double *) malloc(sizeof(double) * n);
	ar3 = (double *) malloc(sizeof(double) * n);
	
	srand(time(NULL));
	
	//#pragma omp parallel for
	for(int i = 0; i < n; i++) ar1[i] = 1 + rand()%(23-14);
	
	//#pragma omp parallel for
	for(int i = 0; i < n; i++) ar2[i] = 1 + rand()%(23-14);
	
	double a = omp_get_wtime();
	for(int i = 0; i < n; i++) 
	{
		ar3[i] = ar1[i] + ar2[i];
		printf("sfhd\n");
	}
	printf("%lf", omp_get_wtime() - a);
	
	a = 0;
	for(int i = 0; i < n; i++) ar3[i] = 0;
	printf("\n");
	
	a = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0; i < n; i++) 
	{
		ar3[i] = ar1[i] + ar2[i];
		printf("sfhd\n");
	}
	printf("%lf", omp_get_wtime() - a);
	
	
  return 0;
}