#include <stdio.h>

int main()
{
// % - mod
// / - div

int m,n,l;
printf("Enter two numbers: ");
scanf("%d%d",&n,&m);
	
	while (m>0)
		{
		printf("%d %d\n",n,m);
		l=n;
		n=m;
		m=l%m;
		}
		
return n;
}