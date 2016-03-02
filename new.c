#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n = 10;
	double *shootingX = (double *)malloc(sizeof(double)*n);
	int i;
	for(i = 0; i < n; i++)
	{
		*(shootingX+i) = i;
	}
	for(i = 0; i < n/2; i++)
	{
		*(shootingX+i) = *(shootingX+(n-i-1));
	}
}