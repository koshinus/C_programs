#include <stdio.h>

int main()
{
  int n,m,i;
  double a,b,d;
  printf ("Enter the n-th and m-th number of arithmetical progression: ");
  scanf ("\n %lf%lf", &a,&b);
  printf ("Enter indexes of this numbers: ");
  scanf ("\n %d%d", &n,&m);

	d=(b-a)/(m-n);
	for(i=n; i<=m; i++) 
		{
			a+=d; 
			printf("\n %lf",a);
		}
		
  return 0;
}