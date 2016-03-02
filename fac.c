#include <stdio.h>

int main()
{
  int n,S,i;
  printf ("Enter your number: ");
  scanf ("\n %d", &n);
  S=1;

	if (n<0)
		{
		printf("Your number must be not less than zero.\n");
		main ();
		}

	else if (n>0)
		{
			for(i=1; i<=n; i++) S*=i;
			printf("Factorial is equal %d ", S);
		}
	
	else if (n == 0) printf("Factorial of 0 is 1");
	
  return 0;
}