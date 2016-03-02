#include <stdio.h>

int GCD(int n, int m)
{
	int l;
	while (m>0)
	{
		l = n;
		n = m;
		m = l%m;
	}
	return n;
}

int main()
{

	int k, i, j, gcd;

	printf("Enter your number: ");
	scanf("%d", &k);

	int a1[k],a2[k];
	
	j = 0;
	for (i = 0; i<k; i++)
	{
		printf("Enter next element of array: ");
		scanf("%d", &a1[i]);
		a2[i] = a1[i];
	}
	for (i = 0; i<k; i++)
	{
		for (j = 0; j<k; j++)
		{
			gcd = GCD(a1[i], a2[j]);
			if (gcd == 1) printf("(%d;%d)\n", a1[i], a2[j]);
		}
	}
	return 0;
}