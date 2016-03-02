#include <stdio.h>

int main()
{
  int n,i;
  double a,S;
  printf ("Enter the number: ");
  scanf ("%lf", &a);
  printf ("Enter power of number: ");
  scanf ("%d", &n);

	S=1;
	if (n<0)
	{
	a=1/a;
	n=-n;
	}
	for(i=0; i<n; i++) S*=a;
		
  printf ("Number %lf is the %dth power",S,n,a);
  return 0;
}