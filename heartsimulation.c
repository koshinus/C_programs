#include<stdio.h>
#include<stdlib.h>

double determinant(double** A)
{
	
	return 	 A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1]
			-
			(A[0][2]*A[1][1]*A[2][0] + A[0][1]*A[1][0]*A[2][2] + A[0][0]*A[1][2]*A[2][1]);
}

int main()
{
	int i, j, n;
	double** A = (double** )malloc(3 * sizeof(double* ));
	for(i = 0; i < 3; i++) A[i] = (double* )malloc(3 * sizeof(double));
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++) 
		{
			scanf("%lf", &n);
			A[i][j] = n;
		}
	}
	printf("%lf", determinant(A));
	return 0;
}