#include <stdio.h>

int main()
{
	int i, j, k, m, n;

	printf("Enter the two numbers: ");
	scanf("%d %d", &n, &m);

	int a1[n], a2[m], a3[m+n];


	for (i = 0; i<n; i++)
	{
		printf("Enter next element of first array: ");
		scanf("%d", &a1[i]);
	}
	for (i = 0; i<m; i++)
	{
		printf("Enter next element of second array: ");
		scanf("%d", &a2[i]);
	}

	i = 0;
	j = 0;
	for (k = 0; k < m + n; k++)
	{
		if (i == n)
		{
			while (k < m + n)
			{
				a3[k] = a2[j];
				j++;
				k++;
			}
		}
		else if (j == m)
		{
			while (k < m + n)
			{
				a3[k] = a1[i];
				i++;
				k++;
			}
		}
		else if (a1[i]>a2[j])
		{
			a3[k] = a2[j];
			j++;
		}
		else
		{
			a3[k] = a1[i];
			i++;
		}
	}
	for(i=0;i<n;i++) printf("%d ",a1[i]);
	printf("\n");
	for(j=0;j<m;j++) printf("%d ",a2[j]);
	printf("\n");
	for(k=0;k<m+n;k++) printf("%d ",a3[k]);
  return 0;
}