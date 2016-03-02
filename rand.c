#include <stdio.h>
#include <stdlib.h>
int MAX(int a, int b)
{
	return (a>b)? a : b;
}

int MIN(int a, int b)
{
	return (a<b)? a : b;
}

int main()
{
	FILE *f;
	if ((f = fopen("randnum.txt","rt")) == NULL)
		{
		printf("Impossible to open or make file\n");
		return 1;
		}
	int n,a,S,max,min,i;
	
	fscanf(f, "%d%d", &n, &a);
	S=a;
	max=a;
	min=a;
	
	for (i=0; i<=n-2; i++)
	{
		fscanf(f, "%d", &a);
		min = MIN(min,a);
		max = MAX(max,a);
		S+=a;
	}
	printf("Maximum is %d\n", max);
	printf("Minimum is %d\n", min);
	printf("Sum is %d\n", S);
	fclose(f);
    return 0;
}