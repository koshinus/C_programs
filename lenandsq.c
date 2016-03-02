#include <stdio.h>
#include <math.h>

int main()
{
  double Pi,r,s,l;
  printf ("Enter radius of circle: ");
  scanf ("\n %lg", &r);

	Pi = 3.14159265358979323846;
	s = r*r*Pi;
	l = 2*Pi*r;

  printf ("Square of circle is %g \n", s);
  printf ("Length of circle is %g \n ", l);
  return 0;
}