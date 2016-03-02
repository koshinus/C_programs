#include <stdio.h>

int main()
{
  double n,m,k,l;
  printf ("Enter 2 complex number: ");
  scanf ("\n %lf%lf%lf%lf", &n,&m,&k,&l);
  printf ("Product is %lf+%lfi \n", n*k-m*l,k*m+l*n);
  printf ("Ratio is %lf+%lfi \n", ((n*k+m*l)/(k*k+l*l)), ((k*m-l*n)/(k*k+l*l)));
  printf ("Sum is %lf+%lfi \n", n+k, m+l);
  printf ("Difference is %lf+%lfi \n", n-k,m-l);
  return 0;
}