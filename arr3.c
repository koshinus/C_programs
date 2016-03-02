#include <stdio.h>

int main()
{

	int m, n=0, k, a[10], i;

	printf("Enter your number: ");
	scanf_s("%d", &m);

	k = m;
	while (m>0)
	{
		m = m / 10;
		n += 1;
	}

	n -= 1;
	for (i = 0; i<=n; i++)
	{
		a[n - i] = k % 10;
		k = k / 10;
	}

	for (i = 0; i<=n; i++)
	{
		if (i != n) printf("%d*10^%d + ", a[i], n - i);
		else printf("%d.", a[n]);
	}

	return 0;
}