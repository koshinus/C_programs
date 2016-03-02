#include <stdio.h>
#include <stdlib.h>
 
int main()
{
	FILE *f;
		
	if ((f = fopen("randnum.txt","rt")) == NULL)
		{
		printf("Impossible to open or make file\n");
		exit(1);
		}
	else
		{
		int n;
		fscanf(f,"%d",&n);
		printf("%d",n);
		
		int S,x,Mn,Mx,i;
		for(i=0;i<=n;i++)
			{
			if (i==n) break;
			else
				{
				fscanf(f,"%d",&x);
				printf("%d ",x);
				S+=x;
				printf("%d ",S);
				if (i=1) { Mn=x; Mx=x; }
				else { Mn=min(x,Mn); Mx=max(x,Mx); }
				}
			}
		printf("Sum is equal %d\n", S);
		printf("Maximum is equal %d\n", Mx);
		printf("Minimum is equal %d\n", Mn);
		}
	fclose(f);
	return 0;
}