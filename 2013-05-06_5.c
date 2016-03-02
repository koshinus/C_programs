#include <stdio.h>

int main ()
{
  int cnt, n, i, k;

  printf ("Enter quantity of numbers: ");
  scanf ("%d", &cnt);

  for (i = 1, k = 0; i <= cnt; i++)
  {
    printf ("Enter an integer: ");
	  scanf ("%d", &n);
	  if (n%2 == 0)
    {
	    k++;
    }
  }

  printf ("You have entered %d number(s). There are %d even(s)\n", 
    cnt, k);

  return 0;
}











