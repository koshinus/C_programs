#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *GenArray(int n,int a, int b)
{	
int i;
int *ar;
	srand(time(NULL));
	ar = (int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++) ar[i]=a+rand()%(b-a+1);
	return ar;
}

int main()
{

	int n,a,b,*ar,i;

	printf("Enter 3 numbers: ");
	scanf("%d%d%d", &n,&a,&b);
	
	ar = GenArray(n,a,b);
	for(i=0;i<n;i++) printf("%d ",ar[i]);
	free(ar);
	return 0;
}