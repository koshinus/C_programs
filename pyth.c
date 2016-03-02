#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i,n,j;
	
	printf("Enter the number: ");
	scanf("%d",&n);
	
	FILE *f;
	if ((f = fopen("pythagoras.txt","wt")) == NULL)
		{
		printf("Impossible to open or make file\n");
		exit(1);
		}
    
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
		if (j==n) fprintf(f,"%3d\n",i*j);
		else fprintf(f,"%3d ",i*j);
		}
	}
	fclose(f);
    return 0;
}