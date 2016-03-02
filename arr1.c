#include <stdio.h>

int main()
{
  int n,a1[n],a2[n],i,a;
  printf("kjeg");
  FILE *f;
	if ((f = fopen("Array.txt","rt")) == NULL)
		{
		printf("Impossible to open or make file\n");
		return 1;
		}
	else printf("kjeg");
	fscanf (f,"%d", &n);
	
	for (i = 0; i<n; i++)
		{
		printf("jhff");
		fscanf(f,"%d",&a1[i]);
		a2[n-i-1]=a1[i];
		}
	for(i=0;i<n;i++)
		{
		if (a1[i]!=a2[i]) 
			{
			printf("Array isn't polyndrom");
			break;
			}
		else if (i==n-1) printf("Array is polyndrom");
		}
  return 0;
}