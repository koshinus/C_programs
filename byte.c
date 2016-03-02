#include <stdio.h>

int main()
{
  int a,b,c,a0,b1,b2,c0,res;
  printf ("Enter 3 integer numbers: ");
  scanf ("%d%d%d", &a, &b, &c);
	
	a0=(a&1)<<5;
	b1=(b&2)<<3;
	b2=(b&4)<<1;
	c0=(c&7);
	res=a0|b1|b2|c0;
	printf("%x", res);
	
  return 0;
}