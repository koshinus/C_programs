#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n;
 srand(time(NULL)); 
	int r = rand(); 
	
		do 
		{
			printf ("Enter your guess: ");
			scanf ("\n %d", &n);
			if (n>r)
				{
				printf("Your number is greater\n");
				}
			else if (n<r)
				{
				printf("Your number is less\n");
				}
		}
		while(n!=r);
	printf ("Yes! My number is %d \n", r);
  return 0;
}