#include <stdio.h>

void mySwap (int *, int *);
void badSwap (int, int);

int main ()
{
	int n = 1, m = 2;
	printf ("Before swap: n = %d, m = %d\n", n, m);
	mySwap (&n, &m);
	printf ("After swap: n = %d, m = %d\n", n, m);
	badSwap (n, m);
	printf ("Bad swap: n = %d, m = %d\n", n, m);

	return 0;
}

void mySwap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void badSwap (int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
} 