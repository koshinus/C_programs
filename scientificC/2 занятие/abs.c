#include <stdio.h>

int main()
{
  double r;
  printf ("Enter the real number: ");
  scanf ("%lf", &r);
	
	if (r < 0) r = -r;
	
	printf ("Absolute value of this number is %lf", r);
	
  return 0;
}