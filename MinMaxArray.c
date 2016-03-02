#include <stdio.h>
#include <limits.h>

int MAX(int a, int b)
{
	return (a>b)? a : b;
}

int MIN(int a, int b)
{
	return (a<b)? a : b;
}


void MinMaxArray(int n, int *a, int *max, int *min)
{
int i;
	if (n==0) 
		{
		*min=INT_MIN;
		*max=INT_MAX;
		}
	*min=a[0];
	*max=a[0];
	for (i=1;i<n;i++)
		{
		*min=MIN(*min,a[i]);
		*max=MAX(*max,a[i]);
		}
}
int main()
{
int n,max,min,i;

	printf("Enter the number: ");
	scanf("%d", &n);
int a[n];
	for (i = 0; i<n; i++)
	{
		printf("Enter next element of array: ");
		scanf("%d", &a[i]);
	}
	
	MinMaxArray(n,a,&max,&min);
	printf("%d\n",min);
	printf("%d",max);
	return 0;
}