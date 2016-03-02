#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int brand()
{
  return (rand() << 16) + rand();
}

int randnum(int n, int a, int b)
{
FILE *f;
	if ((f = fopen("randnum.txt","wt")) == NULL)
		{
		printf("Impossible to open or make file\n");
		return 1;
		}
	int i,x;	
	fprintf(f,"%d\n",n);
	
	srand(time(NULL));
	
	for(i=1;i<=n;i++)
	{
		x = a+brand()%(b-a+1);
		if (i>1) fprintf(f," %d",x);
		else fprintf(f,"%d",x);
	}
	fclose(f);
    return 0;
}

int main()
{
	int n,a,b;
	printf("Enter 3 numbers: ");
	scanf("%d%d%d", &n,&a,&b);
	randnum(n, a, b);
return 0;
}