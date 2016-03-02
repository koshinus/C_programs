#include <stdio.h>
#include <math.h>

int main()
{
  int n;
  double E,yk;
  printf ("Enter the number which sqrt you want to know: ");
  scanf ("\n %d", &n);
  printf ("Enter accuracy: ");
  scanf ("\n %lf", &E);

	yk=1;
	do
		{	
			yk=(yk+n/yk)/2;
			printf("%lf\n",yk);
		} 
	while (fabs(yk*yk-n)>E);
	
	printf("%.12lf is the sqrt of %d with %lf accuracy",yk,n,E);
		
  return 0;
}