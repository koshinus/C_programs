#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(double *a, double *b)
{
double s;
	s=*a;
	*a=*b;
	*b=s;
}

void ReverseArray(int n,double *ar)
{	
int i;
	for(i=0;i<n/2;i++) swap(&ar[i],&ar[n-i-1]);
}


int main()
{

	int n,i,a,b;
	printf("Enter the number: ");
	scanf("%d", &n);
	
	double *ar;
	
	ar = (double *)malloc(sizeof(double)*n);
	for(i=0;i<n;i++)
		{
		printf("Enter next element of array: ");
		scanf("%lf", &ar[i]);
		}
		
	ReverseArray(n,ar);
	for(i=0;i<n;i++) printf("%lf ",ar[i]);
	free(ar);
	return 0;
}