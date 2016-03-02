#include <stdio.h>
#include <stdlib.h>

int main()
{
	double ai,x0,V;
	int n,i;
	
	
	FILE *f;
	f = fopen("poly.txt","rt");
	if (f == NULL)
		{
		printf("Impossible to open or make file\n");
		return 1;
		}
	
	fscanf(f,"%d",&n);
	fscanf(f,"%lf",&x0);
	printf("%d %lf\n", n, x0);
	
	for (i=n+1;i>0;i--)
	{	
		fscanf(f,"%lf",&ai);
		printf("%lf\n",ai);
		V=V*x0+ai;
	}
	printf("Value of polynomial in point %lf is %lf",x0,V);
	fclose(f);
	return 0;
}