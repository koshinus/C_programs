#include <stdio.h>
#include <stdlib.h>

int SortArray(int n, unsigned char *ar)
{
	int i, a=0, b=0, c=0;
	/*	int count[3] = { 0, 0, 0 };
	for (i = 0; i < n; ++i)
	count[ ar[i]-1 ]++;
	int j;
	for (i = j = 0; j < 3; ++j)
	for (; count[j]--; )
	ar[ i++ ] = j+1;

	*/
	for (i = 0; i<n; i++)

		switch (ar[i])
	{
		case(1) :
		{
					  a++;
					  break;
		}
		case(2) :
		{
					  b++;
					  break;
		}
		case(3) :
		{
					  c++;
					  break;
		}
	}
	for (i = 0; i<a; i++) 
	{
	ar[i] = 1;
	}
	for (i = a; i<a+b; i++)
	{
	ar[i] = 2;
	}
	for (i = a+b; i<n; i++)
	{
	ar[i] = 3;
	}
	return 0;
}

int main()
{
	int n, i;
	unsigned char *ar;

	printf("Enter the number: ");
	scanf("%d", &n);

	ar = (unsigned char *)malloc(sizeof(unsigned char)*n);
	for (i = 0; i<n; i++)
	{
		printf("Enter next element of array: ");
		scanf("%hhu", &ar[i]);
	}

	SortArray(n, ar);
	for (i = 0; i<n; i++) printf("%hhu ", ar[i]);
	free(ar);
	return 0;
}