#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int brand()
{
  return (rand() << 16) + rand();
}

int main()
{
	int res;
	
	srand(time(NULL));
	res = brand();
	printf("%d",res);
	
return 0;
}