#include <stdio.h>
#include <math.h>

int main()
{
  double a0,d;
  int n;
  printf ("Enter 2 real numbers: ");
  scanf ("%lf %lf", &a0, &d);
  printf ("Enter tne number of progression term: ");
  scanf ("%d", &n);


  printf ("%lf", a0+n*d);
  return 0;
}
