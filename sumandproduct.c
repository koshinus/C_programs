#include <stdio.h>
//#include <math.h>

int main()
{
  int n,m;
  double k,l;
  printf ("Enter 4 numbers: ");
  scanf ("\n %d%d%lg%lg", &n,&m,&k,&l);

	k = k*l;
	n = n+m;

  printf ("Product is %lg \n", k);
  printf ("Sum is %d \n", n);
  return 0;
}