#include <stdio.h>

void inc_array (int size, int *mas, int v)
{
	int k;
	for (k = 0; k < size; k++)
		mas[k] += v;
}

int main ()
{
	int n, inc, i;
	int *ar;

	printf ("Enter size: ");
	scanf("%d", &n);

	ar = (int *)calloc (n, sizeof(int));
	for (i = 0; i < n; i++)
	{
		printf ("ar[%d] = ", i);
		scanf ("%d", &ar[i]);
	}

	printf ("Enter increment: ");
	scanf ("%d", &inc);

	inc_array (n, ar, inc);

	printf ("After increment: ");
	for (i = 0; i < n; i++)
		printf ("%d ", ar[i]);
	printf ("\n\n");

	printf ("Enter another increment: ");
	scanf ("%d", &inc);

	inc_array (n, ar, inc);

	printf ("After the second increment: ");
	for (i = 0; i < n; i++)
		printf ("%d ", ar[i]);
	printf ("\n");

	return 0;
}