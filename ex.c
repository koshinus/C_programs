#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
int Scal(int *ar,int *br, int n,int *s)
{
int i;
*s=0;
	for (i=0;i<n;i++) 
	{
	*s+=ar[i]*br[i];
	}
	return *s;
}

int main()
{
int n,c1,c2,c3,i;
double cos;
	printf("Enter the number: ");
	scanf("%d",&n);
	int *ar;
	int *br;
	
	ar = (int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++) 
	{
	printf("Enter the element of array: ");
	scanf("%d",&ar[i]);
	}
	br = (int *)malloc(sizeof(int)*n);
	printf("\n");
	for (i=0;i<n;i++) 
	{
	printf("Enter the element of array: ");
	scanf("%d",&br[i]);
	}
	Scal(ar,ar,n,&c1);
	Scal(br,br,n,&c2);
	if ((c1==0)&&(c2==0)) printf("1");
	else if ((c1==0)||(c2==0)) printf("0");
	else 
	{
	Scal(ar,br,n,&c3);
	cos = c3/(sqrt(c1)*sqrt(c2));
	}
	if (cos==1) printf("1");
	else printf("0");
	return 0;
}