#include <stdio.h>

int main()
{
  int n,i,a,b,d;
  printf ("Enter index of fibonacci numbers: ");
  scanf ("%d", &n);

  if (n==0) printf("1\n");
  else if (n==1) 
	{
	printf("1\n");
	printf("1\n");
	}
  else
	{
	a=1;
	b=1;
	d=1;
	printf("%d\n",a);
	printf("%d\n",b);
	for(i=1; i<n; i++) 
		{
			a=d;
			d=b;
			b=d+a;
			printf("%d\n",b);
		}
	}	
  return 0;
}