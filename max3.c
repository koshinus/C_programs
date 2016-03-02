#include <stdio.h>
	
int MAX(int a, int b)
	{
	if (a>b) return a;
	else return b;
	}
	
void max3(int n, int k, int l)
	{
	int max;
	max=MAX(n,MAX(k,l));
	}
	
int main()
{

	int n,k,l,m;
	printf("Enter three numbers: ");
	scanf("%d%d%d",&n,&k,&l);
	m=max3(n,k,l);
	printf("Maximum of %d,%d,%d is %d", n, k, l, m);
	
return 0;
}