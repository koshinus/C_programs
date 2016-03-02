#include <stdio.h>

int main()
{
	int i = 0, n, j, count = 0, sum = 0, from = 0, to;

	printf("Enter your number: ");
	scanf("\n %d", &n);

	to = n - 1;

	int a[n][n];
		
	i = 0;
	while (sum < n*n)
	{
		switch (count % 4)
		{
		case(0):
			{
				for (j = from; j <= to; j++)
					{
						sum++;
						a[i][j] = sum;
					}
				from++;
				count++;
				j--;
				break;
			}
		case(1) :
			{
				for (i = from; i <= to; i++)
					{
						sum++;
						a[i][j] = sum;
					}
				from--;
				to--;
				count++;
				i--;
				break;
			}
		case(2) :
			{
				for (j = to; j >= from; j--)
				{
					sum++;
					a[i][j] = sum;
				}
				from++;
				count++;
				j++;
				break;
			}
		case(3) :
			{
				for (i = to; i >= from; i--)
				{
					sum++;
					a[i][j] = sum;
				}
				count++;
				i++;
			break;
			}
		}
	}
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			if (j != n - 1) printf("%3d ", a[i][j]);
			else printf("%3d\n", a[i][j]);
		}
	}
	return 0;
}